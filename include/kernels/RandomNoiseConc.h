// Phase-field model of solute precipitation / dissolution
// Created by Zexuan Xu, Idaho National Lab
// This is the random noise term for concentration equation to generate sidebranches

#ifndef RandomNoiseConc_H
#define RandomNoiseConc_H

#include "Kernel.h"

//Forward Declarations
class RandomNoiseConc;


template<>
InputParameters validParams<RandomNoiseConc>();

class RandomNoiseConc : public Kernel
{
public:
  RandomNoiseConc(const std::string & name, InputParameters parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  VariableValue & _pf;
  
  Real _amplitude_beta;
  Real _random;

  
  
};

#endif //RandomNoiseConc_H
