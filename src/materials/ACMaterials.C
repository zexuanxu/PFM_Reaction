// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

#include "ACMaterials.h"

template<>
InputParameters validParams<ACMaterials>()
{
  InputParameters params = validParams<Material>();
  params.addParam<Real>("epsilon", "coefficient related the interface thickness, and the phase field parameter diffusion rate");
  params.addParam<Real>("lambda", "coefficient to control the strength of coupling between concentration field and phase field");
  return params;
}

ACMaterials::ACMaterials(const std::string & name,
                       InputParameters parameters) :
    Material(name, parameters),

// epsilon is named as E in kernels of input file
// lambda is named as L in kernels of input file   
    
    _E(declareProperty<Real>("E")),
    _L(declareProperty<Real>("L")),

    _epsilon(getParam<Real>("epsilon")),
    _lambda(getParam<Real>("lambda"))
    
{}

void
ACMaterials::computeProperties()
{
   for (unsigned int qp = 0; qp < _qrule->n_points(); ++qp)
   {
     _E[qp] = _epsilon;
     _L[qp] = _lambda;
    
   }
}
