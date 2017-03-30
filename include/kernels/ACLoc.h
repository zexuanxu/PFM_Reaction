// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
//
// This is the local free enegy function.
// See equation (24) in Xu and Meakin, 2008, Phase-field modeling of solute prcipitation and dissolution, The Journal of Chemical Physics, 129, 014705.
// It is the second term on the right hand side (both f1 and f2) of phase field Allen-Cahn equation.
// f1 = - pf^2 / 2 + pf^4 / 4, f2 = pf - pf^3 / 3
// It's a double-well function with minima at pf = -1 for solid and pf = +1 for liquid.

#ifndef ACLoc_H
#define ACLoc_H

#include "Kernel.h"

//Forward Declarations
class ACLoc;


template<>
InputParameters validParams<ACLoc>();

class ACLoc : public Kernel
{
public:
  ACLoc(const std::string & name, InputParameters parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  std::string _lambda_name;
  MaterialProperty<Real> & _lambda;

  VariableValue & _c;
  
};

#endif //ACLoc_H
