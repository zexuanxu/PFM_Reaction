// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

// This AuxKernel and curvature aux variable DO NOT work!

#include "Curvature.h"

template<>
InputParameters validParams<Curvature>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addCoupledVar ("phase","The phase field order parameter");
  params.addRequiredParam<Real>("coordinate","The coordinate of curvature");
  
  return params;
}

Curvature::Curvature(const std::string & name,
                       InputParameters parameters) :
    AuxKernel(name, parameters),

// coordinate can be 0,1 or 2, as x, y ,z coordinate
    
    _coordinate(getParam<Real>("coordinate")),
    _grad_pf(coupledGradient("phase"))

{}

Real
Curvature::computeValue()
{

  return  _grad_pf[_qp](_coordinate) / _grad_pf[_qp].size()  ;
}

