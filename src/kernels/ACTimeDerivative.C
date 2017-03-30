// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

#include "ACTimeDerivative.h"

template<>
InputParameters validParams<ACTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addRequiredParam<Real>("tau", "characteristic time reflecting the atom mobility");

  // tau here is an optional value. If tau was set as 0.0, it will calculated automatically by other parameters. Otherwise the input value will be used.
  
  params.addRequiredParam<std::string>("epsilon_name", "coeffecient related to the interface thickness");
  params.addRequiredParam<std::string>("diffusivity_name", "diffusivity/diffusion coefficient");
  params.addRequiredParam<std::string>("k_name", "reaction rate");
  params.addRequiredParam<std::string>("kc_name", "stoichiometric coefficient of order unity");
  params.addRequiredParam<std::string>("b_name", "equilibrium concentration / bulk density");
  params.addRequiredParam<std::string>("lambda_name", "coefficient to control the strength of coupling between concentration field and phase field");
  
  return params;
}

ACTimeDerivative::ACTimeDerivative(const std::string & name,
                                             InputParameters parameters) :
    TimeDerivative(name,parameters),

    _tau(getParam<Real>("tau")),

    _epsilon_name(getParam<std::string>("epsilon_name")),
    _diffusivity_name(getParam<std::string>("diffusivity_name")),
    _k_name(getParam<std::string>("k_name")),
    _kc_name(getParam<std::string>("kc_name")),
    _b_name(getParam<std::string>("b_name")),
    _lambda_name(getParam<std::string>("lambda_name")),

    _epsilon(getMaterialProperty<Real>(_epsilon_name)),
    _diffusivity(getMaterialProperty<Real>(_diffusivity_name)),
    _k(getMaterialProperty<Real>(_k_name)),
    _kc(getMaterialProperty<Real>(_kc_name)),
    _b(getMaterialProperty<Real>(_b_name)),
    _lambda(getMaterialProperty<Real>(_lambda_name))
{}

Real
ACTimeDerivative::computeQpResidual()
{

// determine tau first
  
  if (_tau == 0)  

    _t = _lambda[_qp] * _epsilon[_qp] * ( (5 * _epsilon[_qp]) / (3 * _diffusivity[_qp]) + sqrt(2) / _k[_qp]) / (2 * _b[_qp] * _kc[_qp] );
  
  else
    _t = _tau;
  
  return _t * TimeDerivative::computeQpResidual();
}

Real
ACTimeDerivative::computeQpJacobian()
{

  if (_tau == 0)

    _t = _lambda[_qp] * _epsilon[_qp] * ( (5 * _epsilon[_qp]) / (3 * _diffusivity[_qp]) + sqrt(2) / _k[_qp]) / (2 * _b[_qp] * _kc[_qp] );
  
  else

    _t = _tau;
  
  return  _t * TimeDerivative::computeQpJacobian();
}
