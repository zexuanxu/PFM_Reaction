// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

#include "ConcMaterials.h"

template<>
InputParameters validParams<ConcMaterials>()
{
  InputParameters params = validParams<Material>();

  params.addParam<Real>("k","the reaction rate");
  params.addParam<Real>("kc","stoichiometric coefficient of order unity");
  params.addParam<Real>("diffusivity", "diffusivity, actually this is defined as diffusion coefficient");
  params.addParam<Real>("ce", "precipitation/dissolution equilibrium concentration");
  params.addParam<Real>("ps", "density of solid bulks");

  return params;
}

ConcMaterials::ConcMaterials(const std::string & name,
                       InputParameters parameters) :
    Material(name, parameters),
    
    _diffusivity(getParam<Real>("diffusivity")),   
    _kc(getParam<Real>("kc")),
    _k(getParam<Real>("k")),
    _ce(getParam<Real>("ce")),
    _ps(getParam<Real>("ps")),

// B equals to equilibrium concentration divided by sodil bulks density
// kc is named as KC in kernels of input file
// k (reaction rate) is named as K in kernels of input file
// Diffusivity (actually, diffusion coefficient) is named as D in kernels of input file    
    
    _B(declareProperty<Real>("B")),   
    _KC(declareProperty<Real>("KC")),
    _K(declareProperty<Real>("K")),
    _D(declareProperty<Real>("D"))
    
{}

void
ConcMaterials::computeProperties()
{
   for (unsigned int qp = 0; qp < _qrule->n_points(); ++qp)
  {
     _D[qp] = _diffusivity;    
     _B[qp] =  _ce / _ps;
     _K[qp] = _k;
     _KC[qp] = _kc;
    
   }
}
