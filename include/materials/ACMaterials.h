// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)
// 
// See equation (24) in Xu and Meakin, 2008, Phase-field modeling of solute prcipitation and dissolution, The Journal of Chemical Physics, 129, 014705.
// This is the materials object which introduced all parameters needed in the Allen Cahn phase field equation

#ifndef ACMaterials_H
#define ACMaterials_H

#include "Material.h"

//Forward Declarations
class ACMaterials;

template<>
InputParameters validParams<ACMaterials>();

class ACMaterials : public Material
{
public:
  ACMaterials(const std::string & name,
             InputParameters parameters);

protected:
  virtual void computeProperties();

private:

  MaterialProperty<Real> & _E;
  MaterialProperty<Real> & _L;

  Real _epsilon;
  Real _lambda;  
};

#endif //ACMaterial_H
