// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
// 
// See equation (12)-(15) in Xu and Meakin, 2011, Phase-field modeling of two-dimensional solute precipitation/dissolution: Solid fingers and diffusion-limited precipitation, The Journal of Chemical Physics, 129, 014705.
// This is the materials kernels which introduced all DIMENSIONLESS parameters needed in the Allen Cahn phase field equation and concentration equation

#ifndef DimensionlessMaterials_H
#define DimensionlessMaterials_H

#include "Material.h"

//Forward Declarations
class DimensionlessMaterials;

template<>
InputParameters validParams<DimensionlessMaterials>();

class DimensionlessMaterials : public Material
{
public:
  DimensionlessMaterials(const std::string & name,
             InputParameters parameters);

protected:
  virtual void computeProperties();

private:

  MaterialProperty<Real> & _EP;
  MaterialProperty<Real> & _E;
  MaterialProperty<Real> & _P;
  MaterialProperty<Real> & _A;
  MaterialProperty<Real> & _D;

  Real _epsilon_prime;
  Real _epsilon;
  Real _peclet_prime;
  Real _alpha;
  Real _Da;

  
};

#endif //DimensionlessMaterials_H
