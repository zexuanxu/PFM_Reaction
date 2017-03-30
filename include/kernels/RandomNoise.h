// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
// 
// This is the random noise term for phase field Allan-Cahn equation to generate sidebranches

#ifndef RandomNoise_H
#define RandomNoise_H

#include "Kernel.h"

//Forward Declarations
class RandomNoise;


template<>
InputParameters validParams<RandomNoise>();

class RandomNoise : public Kernel
{
public:
  RandomNoise(const std::string & name, InputParameters parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _amplitude_alpha;
  Real _random;
  
  
};

#endif //RandomNoise_H
