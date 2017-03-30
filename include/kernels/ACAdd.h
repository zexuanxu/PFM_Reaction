// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
// 
// See equation (24) in Xu and Meakin, 2008, Phase-field modeling of solute prcipitation and dissolution, The Journal of Chemical Physics, 129, 014705.
// This is the additional term (the last term on the right hand side) of phase field Allen-Cahn equation.
// Curvature term kappa = div (_grad(pf) / grad(pf).size()). For detail, please see equations document
// If _grad_pf.size() > 1e-6, the whole term is calculated.
// If _grad_pf.size() < 1e-6, the whole term is not calculated (this term is 0).
// 3D is an optional in this kernel (I did some tests, but I don't think 3D case works)

#ifndef ACAdd_H
#define ACAdd_H

#include "Kernel.h"

//Forward Declarations
class ACAdd;


template<>
InputParameters validParams<ACAdd>();

class ACAdd : public Kernel
{
public:
  ACAdd(const std::string & name, InputParameters parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  std::string _epsilon_name; 
  MaterialProperty<Real> & _epsilon;
  
  Real kappa;
  Real _t1;
  Real _t2;
  
  Real _div_grad_ux;
  Real _div_grad_uy;

// For 3D use only  
  Real _div_grad_uz;
  
  VariableSecond & _second_u;
  VariablePhiSecond & _second_phi;
  
  
};

#endif //ACAdd_H
