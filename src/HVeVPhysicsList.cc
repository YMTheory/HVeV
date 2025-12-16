
#include "G4UnitsTable.hh"
#include "G4LossTableManager.hh"
#include "G4EmProcessOptions.hh"

#include "HVeVPhysicsList.hh"
//#include "PhysicsList.cc"
#include "G4MicroElecElastic.hh"
#include "G4MicroElecElasticModel.hh"
#include "G4MicroElecInelastic.hh"
#include "G4MicroElecInelasticModel.hh"
#include "G4LossTableManager.hh"
#include "G4EmDNAPhysics.hh"
#include "G4CMPPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"

#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4EmLowEPPhysics.hh"
#include "G4EmStandardPhysicsSS.hh"
#include "G4EmLivermorePolarizedPhysics.hh"
#include "G4EmStandardPhysicsGS.hh"
#include "G4EmStandardPhysicsWVI.hh"
#include "G4IonConstructor.hh"
HVeVPhysicsList::HVeVPhysicsList(): G4VModularPhysicsList() {
//  SetVerboseLevel(verbose);
//  if (verbose) G4cout << "G4CMPPhysicsList::constructor" << G4endl;
    RegisterPhysics(new G4CMPPhysics);
    RegisterPhysics(new G4EmLowEPPhysics());
  //  RegisterPhysics(new G4EmLivermorePolarizedPhysics());
   // RegisterPhysics(new G4CMPPhysics());
//    RegisterPhysics(new G4CMPPhysics);
//    RegisterPhysics(new G4EmStandardPhysicsGS());
//    RegisterPhysics(new G4EmStandardPhysicsWVI());
//    RegisterPhysics(new G4EmStandardPhysics());
// HEP    RegisterPhysics(new G4EmStandardPhysics_option1());
// HEP    RegisterPhysics(new G4EmStandardPhysics_option2());
//    RegisterPhysics(new G4EmStandardPhysics_option3());
//    RegisterPhysics(new G4EmStandardPhysics_option4());
    RegisterPhysics(new G4EmLivermorePhysics());
  //  RegisterPhysics(new G4EmPenelopePhysics());
    RegisterPhysics(new G4HadronElasticPhysics());
  //  RegisterPhysics(new G4HadronInelasticQBBC());
//    RegisterPhysics(new G4IonBinaryCascadePhysics());
//    RegisterPhysics(new G4EmExtraPhysics());
  //  RegisterPhysics(new G4StoppingPhysics());
  ///  RegisterPhysics(new G4EmDNAPhysics());
}

HVeVPhysicsList::~HVeVPhysicsList(){

}

void HVeVPhysicsList::ConstructParticle(){
    G4VModularPhysicsList::ConstructParticle();
}
void HVeVPhysicsList::ConstructProcess(){
    G4VModularPhysicsList::ConstructProcess();
}

void HVeVPhysicsList::SetCuts(){
//    SetCutValue(1*eV, "gamma");
//    SetCutValue(1*eV, "e-");
//    SetCutValue(1*eV, "e+");
}

