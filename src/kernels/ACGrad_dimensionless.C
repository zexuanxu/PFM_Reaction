// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

#include "ACGrad_dimensionless.h"

template<>
InputParameters validParams<ACGrad_dimensionless>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<std::string>("peclet_prime_name", "peclet prime value");
  return params;
}

ACGrad_dimensionless::ACGrad_dimensionless(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),

    _peclet_prime_name(getParam<std::string>("peclet_prime_name")),
    _peclet_prime(getMaterialProperty<Real>(_peclet_prime_name))
{
}

Real
ACGrad_dimensionless::computeQpResidual()
{
  
  return _grad_test[_i][_qp] * _grad_u[_qp] / _peclet_prime[_qp];
}

Real
ACGrad_dimensionless::computeQpJacobian()
{
  return _grad_test[_i][_qp] * _grad_phi[_j][_qp] / _peclet_prime[_qp];
}
