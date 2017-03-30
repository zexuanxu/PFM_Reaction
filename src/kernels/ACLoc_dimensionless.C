// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

#include "ACLoc_dimensionless.h"

template<>
InputParameters validParams<ACLoc_dimensionless>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredParam<std::string>("epsilon_prime_name", "coefficient related the interface thickness");
  params.addRequiredParam<std::string>("peclet_prime_name", "peclet prime value");
  params.addRequiredParam<std::string>("Da_name", "Damkohler number");
  params.addRequiredParam<std::string>("alpha_name", "alpha");
  
  params.addRequiredCoupledVar("concentration","the concentration field coupled in this phase field kernel");
  return params;
}

ACLoc_dimensionless::ACLoc_dimensionless(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _epsilon_prime_name(getParam<std::string>("epsilon_prime_name")),
    _peclet_prime_name(getParam<std::string>("peclet_prime_name")),
    _Da_name(getParam<std::string>("Da_name")),
    _alpha_name(getParam<std::string>("alpha_name")),

    _epsilon_prime(getMaterialProperty<Real>(_epsilon_prime_name)),
     _peclet_prime(getMaterialProperty<Real>(_peclet_prime_name)),   
    _Da(getMaterialProperty<Real>(_Da_name)),    
    _alpha(getMaterialProperty<Real>(_alpha_name)),
    
    _c(coupledValue("concentration"))
{
}


Real
ACLoc_dimensionless::computeQpResidual()
{

// calculate lambda first
  
  _lambda = _peclet_prime[_qp] / (_alpha[_qp] * (1.667 + sqrt(2) / (_Da[_qp] * _epsilon_prime[_qp])));
  
  _l1 = - _test[_i][_qp] * (1 - _u[_qp] * _u[_qp]) * (_u[_qp] - _lambda * _c[_qp])  / _peclet_prime[_qp];

  return _l1;
  
}

Real
ACLoc_dimensionless::computeQpJacobian()
{
  _lambda = _peclet_prime[_qp] / (_alpha[_qp] * (1.667 + sqrt(2) / (_Da[_qp] * _epsilon_prime[_qp])));

  _l2 =  - _test[_i][_qp] * _phi[_j][_qp] * ( 1 - 3 * _u[_qp]*_u[_qp] + 2 * _lambda * _c[_qp] * _u[_qp]) / _peclet_prime[_qp];

  return _l2;
  

}
