// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

#include "ConcAdd.h"

template<>
InputParameters validParams<ConcAdd>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("phase", "The coupled phase field order parameter");
  params.addRequiredParam<std::string>("b_name","equilibrium concentration / bulk density");
  params.addRequiredParam<std::string>("k_name","reaction rate");
  params.addRequiredParam<std::string>("kc_name","stoichiometric coefficient of order unity");
  params.addRequiredParam<std::string>("diffusivity_name", "diffusivity/diffusion coefficient");
  return params;
}

ConcAdd::ConcAdd (const std::string & name,
                  InputParameters parameters) :
    Kernel(name, parameters),


    _b_name(getParam<std::string>("b_name")),   
    _k_name(getParam<std::string>("k_name")),
    _kc_name(getParam<std::string>("kc_name")),
    _diffusivity_name(getParam<std::string>("diffusivity_name")),

    _second_pf(coupledSecond("phase")), 
    _grad_pf(coupledGradient("phase")),
    _pf_dot(coupledDot("phase")),
    _pf(coupledValue("phase")),
    
    _b(getMaterialProperty<Real>(_b_name)),
    _k(getMaterialProperty<Real>(_k_name)),
    _kc(getMaterialProperty<Real>(_kc_name)),
    _diffusivity(getMaterialProperty<Real>(_diffusivity_name))
{}

Real ConcAdd::computeQpResidual()
{

  if (_grad_pf[_qp].size() > 1e-3 )
  {
     
    _t1 = - _test[_i][_qp] * _pf_dot[_qp] * (1 + (_diffusivity[_qp] * _second_pf[_qp].tr() - _pf_dot[_qp]) / (_k[_qp] * _grad_pf[_qp].size()) )/ (2 * _b[_qp] * _kc[_qp]);

    return _t1 ;
    
    }

    else

  {
     _t2 = - _test[_i][_qp] * _pf_dot[_qp] / (2 * _b[_qp] * _kc[_qp]);
    
        return _t2 ;
    
   }

}


Real ConcAdd::computeQpJacobian()
{
  return 0;
}
