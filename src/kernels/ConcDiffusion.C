// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

#include "ConcDiffusion.h"

template<>
InputParameters validParams<ConcDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addRequiredParam<std::string>("diffusivity_name", "diffusion coefficient");
  return params;
}

ConcDiffusion::ConcDiffusion(const std::string & name,
                                             InputParameters parameters) :
    Diffusion(name,parameters),
    _diffusivity_name(getParam<std::string>("diffusivity_name")),
    _diffusivity(getMaterialProperty<Real>(_diffusivity_name))

{}

Real
ConcDiffusion::computeQpResidual()
{
   return _diffusivity[_qp] * Diffusion::computeQpResidual();

}


Real
ConcDiffusion::computeQpJacobian()
{
  return _diffusivity[_qp] * Diffusion::computeQpJacobian();
}

