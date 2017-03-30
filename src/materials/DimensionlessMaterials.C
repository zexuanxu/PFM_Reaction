// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

#include "DimensionlessMaterials.h"

template<>
InputParameters validParams<DimensionlessMaterials>()
{
  InputParameters params = validParams<Material>();
  params.addParam<Real>("epsilon_prime", "coefficient related the interface thickness, and the unit of length");
  params.addParam<Real>("epsilon", "coefficient related the interface thickness"); 
  params.addParam<Real>("peclet_prime", "peclet prime number, which is relevant to the diffusion of the phase field variable ");
  params.addParam<Real>("alpha", "alpha, equals to 1/(2*b*k), b = ce/ps");
  params.addParam<Real>("Da", "Damkohler number");
  return params;
}

DimensionlessMaterials::DimensionlessMaterials(const std::string & name,
                       InputParameters parameters) :
    Material(name, parameters),

// epsilon is named as E in kernels of input file
// epsilon prime is named as EP in kernels of input file
// peclet prime is named as P in kernels of input file
// alpha is named as A in kernels of input file
// Da is named as D in kernels of input file    
    
    _EP(declareProperty<Real>("EP")),
    _E(declareProperty<Real>("E")),
    _P(declareProperty<Real>("P")),
    _A(declareProperty<Real>("A")),
    _D(declareProperty<Real>("D")),

    _epsilon_prime(getParam<Real>("epsilon_prime")),
    _epsilon(getParam<Real>("epsilon")),
    _peclet_prime(getParam<Real>("peclet_prime")),
    _alpha(getParam<Real>("alpha")),
    _Da(getParam<Real>("Da"))
    
{}

void
DimensionlessMaterials::computeProperties()
{
   for (unsigned int qp = 0; qp < _qrule->n_points(); ++qp)
   {
     
     _EP[qp] = _epsilon_prime;
     _E[qp] = _epsilon;
     _P[qp] = _peclet_prime;
     _A[qp] = _alpha;
     _D[qp] = _Da;
     
    
   }
}
