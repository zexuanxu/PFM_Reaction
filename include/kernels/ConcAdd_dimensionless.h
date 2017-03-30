#ifndef ConcAdd_dimensionless_H
#define ConcAdd_dimensionless_H

#include "Kernel.h"

class ConcAdd_dimensionless;

template<>
InputParameters validParams<ConcAdd_dimensionless>();

class ConcAdd_dimensionless : public Kernel
{
public:

  ConcAdd_dimensionless(const std::string & name,
             InputParameters parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  std::string _epsilon_prime_name;
  std::string _Da_name;
  std::string _alpha_name;
  
  MaterialProperty<Real> & _epsilon_prime;
  
  MaterialProperty<Real> & _Da;
  MaterialProperty<Real> & _alpha;
  
  VariableSecond & _second_pf;
  VariableGradient & _grad_pf;
  VariableValue & _pf_dot;
  VariableValue & _pf;
  


  Real _t1;
  Real _t2; 
  
};

#endif //ConcAdd_H
