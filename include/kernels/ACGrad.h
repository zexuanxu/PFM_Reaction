// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
// 
// This is the gradient free enegy function.
// See equation (24) in Xu and Meakin, 2008, Phase-field modeling of solute prcipitation and dissolution, The Journal of Chemical Physics, 129, 014705.
// It is the phase field order parameter diffusion term (the first term on the right hand side) of phase field Allen-Cahn equation.

#ifndef ACGrad_H
#define ACGrad_H

#include "Kernel.h"

//Forward Declarations
class ACGrad;

template<>
InputParameters validParams<ACGrad>();

class ACGrad : public Kernel
{
public:
  ACGrad(const std::string & name, InputParameters parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  std::string _epsilon_name;
  
  MaterialProperty<Real> & _epsilon;


};

#endif //ACGrad_H
