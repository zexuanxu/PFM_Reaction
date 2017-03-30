// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
// This is the concentration diffusion term
// See equation (25) in Xu and Meakin, 2008, Phase-field modeling of solute precipitation and dissolution, The Journal of Chemical Physics, 129, 014705.
// It is the first term on the right hand side of concentration diffusion-reaction equation.
// This kernel doesn't have phase field variable limit here. The concentration diffusion is calcualted within the whole domain (including solid bulks) 


#ifndef ConcDiffusion_H
#define ConcDiffusion_H

#include "Diffusion.h"

// Forward Declarations
class ConcDiffusion;

template<>
InputParameters validParams<ConcDiffusion>();

class ConcDiffusion : public Diffusion
{
public:

  ConcDiffusion(const std::string & name,
                InputParameters parameters);

protected:
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();
  
private:
  std::string _diffusivity_name;
  MaterialProperty<Real> & _diffusivity;

  
};

#endif //ConcDiffusion_H
