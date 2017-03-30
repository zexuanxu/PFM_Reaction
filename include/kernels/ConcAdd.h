// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
// 
// This is the additional reaction term
// See equation (25) in Xu and Meakin, 2008, Phase-field modeling of solute precipitation and dissolution, The Journal of Chemical Physics, 129, 014705.
// It is the second and last term on the right hand side of concentration diffusion-reaction equation.
// If _grad_pf > 1e-6, both the two terms are calculated.
// If _grad_pf < 1e-6, only the second term is calculated

#ifndef ConcAdd_H
#define ConcAdd_H

#include "Kernel.h"

class ConcAdd;

template<>
InputParameters validParams<ConcAdd>();

class ConcAdd : public Kernel
{
public:

  ConcAdd (const std::string & name,
          InputParameters parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:

  std::string _b_name;
  std::string _k_name;
  std::string _kc_name;
  std::string _diffusivity_name;

  VariableSecond & _second_pf;
  VariableGradient & _grad_pf;
  VariableValue & _pf_dot;
  VariableValue & _pf;
  
  MaterialProperty<Real> & _b;
  MaterialProperty<Real> & _k;
  MaterialProperty<Real> & _kc;
  MaterialProperty<Real> & _diffusivity;

  Real _t1;
  Real _t2;
  Real _t;
  
  
  
  
};

#endif //ConcAdd_H
