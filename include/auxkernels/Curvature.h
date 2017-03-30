// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

// This AuxKernel and curvature aux variable DO NOT WORK!
// Because AuxVariable only supports element variable with constant monomials, and nodal variable with linear Lagrange. 


#ifndef Curvature_H
#define Curvature_H

#include "AuxKernel.h"

class Curvature;

template<>
InputParameters validParams<Curvature>();

class Curvature : public AuxKernel
{
public:

  Curvature(const std::string & name,
             InputParameters parameters);

  virtual ~Curvature() {}
  

protected:

  virtual Real computeValue();

private:

  Real _coordinate;
  
  VariableGradient & _grad_pf;
  
};

#endif //Curvature_H
