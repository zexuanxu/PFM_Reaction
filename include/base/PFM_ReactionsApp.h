// Phase-field model of solute precipitation / dissolution
// Author: Zexuan Xu, Idaho National Laboratory
// Contact: Zexuan Xu (xuzexuan@gmail.com) or Hai Huang (hai.huang@inl.gov)

// This is the MooseApp file

#ifndef PFM_Reactions_H
#define PFM_Reactions_H

#include "MooseApp.h"

class PFM_ReactionsApp;

template<>
InputParameters validParams<PFM_ReactionsApp>();

class PFM_ReactionsApp : public MooseApp
{
public:
  PFM_ReactionsApp(const std::string & name, InputParameters parameters);
  virtual ~PFM_ReactionsApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* PFM_Reactions_H */
