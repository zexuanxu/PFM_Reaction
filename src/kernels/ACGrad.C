// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

#include "ACGrad.h"

template<>
InputParameters validParams<ACGrad>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<std::string>("epsilon_name", "coefficient related the interface thickness");

  return params;
}

ACGrad::ACGrad(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),

    _epsilon_name(getParam<std::string>("epsilon_name")),
    _epsilon(getMaterialProperty<Real>(_epsilon_name))
{
}

Real
ACGrad::computeQpResidual()
{
  
  return _epsilon[_qp] * _epsilon[_qp] * _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
ACGrad::computeQpJacobian()
{
  return _epsilon[_qp] * _epsilon[_qp] * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}
