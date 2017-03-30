// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

#include "ACAdd_dimensionless.h"

template<>
InputParameters validParams<ACAdd_dimensionless>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<std::string>("epsilon_name", "coefficient related the interface thickness");
  params.addRequiredParam<std::string>("peclet_prime_name", "peclet prime value");
  return params;
}

ACAdd_dimensionless::ACAdd_dimensionless(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _epsilon_name(getParam<std::string>("epsilon_name")),
    _epsilon(getMaterialProperty<Real>(_epsilon_name)),
    _peclet_prime_name(getParam<std::string>("peclet_prime_name")),
    _peclet_prime(getMaterialProperty<Real>(_peclet_prime_name)),
    _second_u(second()),
    _second_phi(secondPhi())
    
{}

Real
ACAdd_dimensionless::computeQpResidual()
{

  if (_grad_u[_qp].size() > 1e-6 )
  {
    _div_grad_ux = (_grad_u[_qp](0) * _second_u[_qp](0,0)) / _grad_u[_qp].size();
    _div_grad_uy = (_grad_u[_qp](1) * _second_u[_qp](1,1)) / _grad_u[_qp].size();
    
//  3D option  
//    _div_grad_uz = (_grad_u[_qp](2) * _second_u[_qp](2,2)) / _grad_u[_qp].size();
//
// Curvature term
// 
//    kappa = ( _second_u[_qp].tr() - ( _grad_u[_qp](0) * _div_grad_ux +  _grad_u[_qp](1) * _div_grad_uy) / _grad_u[_qp].size()) / _grad_u[_qp].size();
    //   kappa = ( _second_u[_qp].tr() - ( _grad_u[_qp](0) * _div_grad_ux +  _grad_u[_qp](1) * _div_grad_uy) / _grad_u[_qp].size()) / _grad_u[_qp].size();
    
// The laplacian term has two ways to treat. Both of these two treatment are not incorrect (I believe), but the results are different.      
//  _t1 = - _grad_test[_i][_qp] * _grad_u[_qp];
    _t1 = _test[_i][_qp] * _second_u[_qp].tr();

// 2D option
//    
    _t2 =  _test[_i][_qp] * ( _grad_u[_qp](0) * _div_grad_ux +  _grad_u[_qp](1) * _div_grad_uy ) / _grad_u[_qp].size();

// 3D option    
//
//   _t2 =  _test[_i][_qp] * ( _grad_u[_qp](0) * _div_grad_ux +  _grad_u[_qp](1) * _div_grad_uy + _grad_u[_qp](2) * _div_grad_uz ) / _grad_u[_qp].size();
    
    return _epsilon[_qp] * ( _t1 - _t2 ) / _peclet_prime[_qp];
  }
  
  else

    return 0;
  
}

Real
ACAdd_dimensionless::computeQpJacobian()
{
  // The Jacaobian of this kernel is not calculated
  
  return 0;
     
}

