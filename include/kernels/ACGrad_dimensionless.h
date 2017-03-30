// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
//       
// This is the gradient free enegy function.
// See equation (12) in Xu and Meakin, 2011, Phase-field modeling of two-dimensional solute precipitation/dissolution: Solid fingers and diffusion-limited precipitation, The Journal of Chemical Physics, 129, 014705.
// It is the phase field order parameter diffusion term (the first term on the right hand side) of phase field DIMENSIONLESS Allen-Cahn equation.


#ifndef ACGrad_dimensionless_H
#define ACGrad_dimensionless_H

#include "Kernel.h"

//Forward Declarations
class ACGrad_dimensionless;

template<>
InputParameters validParams<ACGrad_dimensionless>();

class ACGrad_dimensionless : public Kernel
{
public:
  ACGrad_dimensionless(const std::string & name, InputParameters parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  std::string _peclet_prime_name;
  
  MaterialProperty<Real> & _peclet_prime;


};

#endif //ACGrad_dimensionless_H
