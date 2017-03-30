#include "ConcAdd_dimensionless.h"

template<>
InputParameters validParams<ConcAdd_dimensionless>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("phase", "The coupled phase field order parameter");
  params.addRequiredParam<std::string>("epsilon_prime_name", "coefficient related the interface thickness");
  params.addRequiredParam<std::string>("Da_name", "Damkohler number");
  params.addRequiredParam<std::string>("alpha_name", "alpha");
  
  return params;
}

ConcAdd_dimensionless::ConcAdd_dimensionless(const std::string & name,
                       InputParameters parameters) :
    Kernel(name, parameters),

    _epsilon_prime_name(getParam<std::string>("epsilon_prime_name")),
    _Da_name(getParam<std::string>("Da_name")),
    _alpha_name(getParam<std::string>("alpha_name")),
    
   _epsilon_prime(getMaterialProperty<Real>(_epsilon_prime_name)),
    _Da(getMaterialProperty<Real>(_Da_name)),   
    _alpha(getMaterialProperty<Real>(_alpha_name)),
    
    _second_pf(coupledSecond("phase")), 
    _grad_pf(coupledGradient("phase")),
    _pf_dot(coupledDot("phase")),
    _pf(coupledValue("phase"))   
{}

Real ConcAdd_dimensionless::computeQpResidual()
{

    
  if (_grad_pf[_qp].size() > 1e-6 )
  {
     
    _t1 = - _test[_i][_qp] * _pf_dot[_qp] * _alpha[_qp] * (1 + ( (_second_pf[_qp].tr() - _pf_dot[_qp]) / (_Da[_qp] * _epsilon_prime[_qp] * _grad_pf[_qp].size()) ));

    return _t1 ;
    }

    else

  {
    
     _t2 = - _test[_i][_qp] * _pf_dot[_qp] * _alpha[_qp];

     return _t2 ;
    
   }

}


Real ConcAdd_dimensionless::computeQpJacobian()
{
  return 0;
}
