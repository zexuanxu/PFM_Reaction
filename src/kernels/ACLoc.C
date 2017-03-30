// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

#include "ACLoc.h"

template<>
InputParameters validParams<ACLoc>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<std::string>("lambda_name", "coefficient to control the strength of coupling between concentration field and phase field");
  params.addRequiredCoupledVar("concentration","the concentration field coupled in this phase field kernel");
  return params;
}

ACLoc::ACLoc(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _lambda_name(getParam<std::string>("lambda_name")),
    _lambda(getMaterialProperty<Real>(_lambda_name)),
    _c(coupledValue("concentration"))
{
}


Real
ACLoc::computeQpResidual()
{
  
  return - _test[_i][_qp] * (1 - _u[_qp]*_u[_qp]) * ( _u[_qp] - _lambda[_qp] * _c[_qp] ) ;
  
}

Real
ACLoc::computeQpJacobian()
{

  return - _test[_i][_qp] * _phi[_j][_qp] * ( 1 - 3 * _u[_qp]*_u[_qp]  + 2 * _lambda[_qp] * _c[_qp] * _u[_qp]);


}
