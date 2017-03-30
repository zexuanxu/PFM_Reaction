// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
//
// See equation (12) in Xu and Meakin, 2011, Phase-field modeling of two-dimensional solute precipitation/dissolution: Solid fingers and diffusion-limited precipitation, The Journal of Chemical Physics, 129, 014705.
// This is the additional term (the last term on the right hand side) of the phase field DIMENSIONLESS Allen-Cahn equation.
// If _grad_pf.size() > 1e-6, the whole term is calculated.
// If _grad_pf.size() < 1e-6, the whole term is not calculated (this term is 0).
// 3D is an optional in this kernel (I did some tests, but I don't think 3D case works)

#ifndef ACAdd_dimensionless_H
#define ACAdd_dimensionless_H

#include "Kernel.h"

//Forward Declarations
class ACAdd_dimensionless;


template<>
InputParameters validParams<ACAdd_dimensionless>();

class ACAdd_dimensionless : public Kernel
{
public:
  ACAdd_dimensionless(const std::string & name, InputParameters parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  std::string _epsilon_name; 
  MaterialProperty<Real> & _epsilon;

  std::string _peclet_prime_name;
  MaterialProperty<Real> & _peclet_prime;
  
  
  Real kappa;
  Real _t1;
  Real _t2;
  
  
  Real _div_grad_ux;
  Real _div_grad_uy;

  VariableSecond & _second_u;
  VariablePhiSecond & _second_phi;
  
  
};

#endif //ACAdd_dimensionless_H
