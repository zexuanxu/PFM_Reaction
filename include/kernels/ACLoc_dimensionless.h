// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
//
// This is the gradient free enegy function.
// See equation (12) in Xu and Meakin, 2011, Phase-field modeling of two-dimensional solute precipitation/dissolution: Solid fingers and diffusion-limited precipitation, The Journal of Chemical Physics, 129, 014705.
// It is the phase field order parameter diffusion term (the first term on the right hand side) of phase field Allen-Cahn equation.

#ifndef ACLoc_dimensionless_H
#define ACLoc_dimensionless_H

#include "Kernel.h"

//Forward Declarations
class ACLoc_dimensionless;


template<>
InputParameters validParams<ACLoc_dimensionless>();

class ACLoc_dimensionless : public Kernel
{
public:
  ACLoc_dimensionless(const std::string & name, InputParameters parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:

  std::string _epsilon_prime_name;
  std::string _peclet_prime_name;
  std::string _Da_name;
  std::string _alpha_name;
  
  MaterialProperty<Real> & _epsilon_prime;
  MaterialProperty<Real> & _peclet_prime;
  MaterialProperty<Real> & _Da;
  MaterialProperty<Real> & _alpha;
  
  VariableValue & _c;

  Real _lambda;
  Real _l1;
  Real _l2;
  
  
};

#endif //ACLoc_dimensionless_H
