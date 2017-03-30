// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

#include "PFM_ReactionsApp.h"
#include "Moose.h"
#include "Factory.h"
#include "AppFactory.h"

// ics (Initial condition) header file
#include "SmoothCircleIC.h"

// Kernel header files

// Dimensional equation kernels header files
#include "ACAdd.h"
#include "ACGrad.h"
#include "ACLoc.h"
#include "ACTimeDerivative.h"
#include "ConcAdd.h"
#include "ConcDiffusion.h"
#include "Convection.h"

// Dimensionless equation kernels header files
#include "ACAdd_dimensionless.h"
#include "ACLoc_dimensionless.h"
#include "ACGrad_dimensionless.h"
#include "ConcAdd_dimensionless.h"

// Random noise kernels header files
#include "RandomNoise.h"
#include "RandomNoiseConc.h"

// AuxKernel header file
#include "Curvature.h"

// Materials header files
#include "ACMaterials.h"
#include "ConcMaterials.h"
#include "DimensionlessMaterials.h"

template<>
InputParameters validParams<PFM_ReactionsApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

PFM_ReactionsApp::PFM_ReactionsApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  PFM_ReactionsApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  PFM_ReactionsApp::associateSyntax(_syntax, _action_factory);
}

PFM_ReactionsApp::~PFM_ReactionsApp()
{
}

void
PFM_ReactionsApp::registerApps()
{
  registerApp(PFM_ReactionsApp);
}

void
PFM_ReactionsApp::registerObjects(Factory & factory)
{
  registerInitialCondition(SmoothCircleIC);
  
  registerKernel(ACAdd);
  registerKernel(ACGrad);
  registerKernel(ACLoc);
  registerKernel(ACTimeDerivative);
  registerKernel(ConcAdd);
  registerKernel(ConcDiffusion);
  registerKernel(Convection);
  
  registerKernel(ACAdd_dimensionless);
  registerKernel(ACLoc_dimensionless);
  registerKernel(ACGrad_dimensionless);
  registerKernel(ConcAdd_dimensionless);

  registerKernel(RandomNoise);
  registerKernel(RandomNoiseConc);
  
  registerAux(Curvature);
  
  registerMaterial(ACMaterials);
  registerMaterial(ConcMaterials);
  registerMaterial(DimensionlessMaterials);
  
  
}

 void
 PFM_ReactionsApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
 {}
