// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
// 
// See equation (25) in Xu and Meakin, 2008, Phase-field modeling of solute prcipitation and dissolution, The Journal of Chemical Physics, 129, 014705.
// This is the materials object which introduced all parameters needed in the concentration diffusion and/or convenction, and reaction equation

#ifndef ConcMaterials_H
#define ConcMaterials_H

#include "Material.h"

//Forward Declarations
class ConcMaterials;

template<>
InputParameters validParams<ConcMaterials>();

class ConcMaterials : public Material
{
public:
  ConcMaterials(const std::string & name,
             InputParameters parameters);

protected:
  virtual void computeProperties();

private:

  Real _diffusivity;
  Real _kc;
  Real _k;
  Real _ce;
  Real _ps;
  
  MaterialProperty<Real> & _B;
  MaterialProperty<Real> & _KC; 
  MaterialProperty<Real> & _K;
  MaterialProperty<Real> & _D;
  
};

#endif //ConcMaterial_H
