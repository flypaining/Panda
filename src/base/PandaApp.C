#include "PandaApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

template<>
InputParameters validParams<PandaApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

PandaApp::PandaApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  PandaApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  PandaApp::associateSyntax(_syntax, _action_factory);
}

PandaApp::~PandaApp()
{
}

// External entry point for dynamic application loading
extern "C" void PandaApp__registerApps() { PandaApp::registerApps(); }
void
PandaApp::registerApps()
{
  registerApp(PandaApp);
}

// External entry point for dynamic object registration
extern "C" void PandaApp__registerObjects(Factory & factory) { PandaApp::registerObjects(factory); }
void
PandaApp::registerObjects(Factory & factory)
{
  registerKernel(LaplaceYoung);
}

// External entry point for dynamic syntax association
extern "C" void PandaApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { PandaApp::associateSyntax(syntax, action_factory); }
void
PandaApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
