/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef DIFFUSION_H
#define DIFFUSION_H

#include "Kernel.h"

class Diffusion;

template<>
InputParameters validParams<Diffusion>();


class Diffusion : public Kernel
{
public:
  Diffusion(const std::string & name, InputParameters parameters);
  virtual ~Diffusion();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
};


#endif /* DIFFUSION_H */
