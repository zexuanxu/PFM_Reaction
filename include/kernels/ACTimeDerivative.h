// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
//             
// This is the local free enegy function.
// See equation (24) in Xu and Meakin, 2008, Phase-field modeling of solute prcipitation and dissolution, The Journal of Chemical Physics, 129, 014705.
// It is the time derivative term on the left hand side of phase field Allen-Cahn equation.
// If tau is assigned as 0, it will calculated automatically by the eqation (54) in Xu and Meakin, 2008.
// If tau is not 0, the assigned value will be used.

#ifndef ACTimeDerivative_H
#define ACTimeDerivative_H

#include "TimeDerivative.h"

// Forward Declarations
class ACTimeDerivative;

template<>
InputParameters validParams<ACTimeDerivative>();

class ACTimeDerivative : public TimeDerivative
{
public:

  ACTimeDerivative(const std::string & name,
                        InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  Real _tau;
  
  std::string _epsilon_name;
  std::string _diffusivity_name;
  std::string _k_name;
  std::string _kc_name;
  std::string _b_name;
  std::string _lambda_name;
  
  MaterialProperty<Real> & _epsilon;
  MaterialProperty<Real> & _diffusivity;
  MaterialProperty<Real> & _k;
  MaterialProperty<Real> & _kc;
  MaterialProperty<Real> & _b;
  MaterialProperty<Real> & _lambda;
  
  Real _t;
  
};

#endif //ACTimeDerivative_H
