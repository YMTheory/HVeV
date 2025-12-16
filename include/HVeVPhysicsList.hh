#ifndef HVEVPHYSICSLIST_HH
#define HVEVPHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4VPhysicsConstructor.hh"
#include "G4ProductionCuts.hh"
#include "G4Scintillation.hh"

class HVeVPhysicsList : public G4VModularPhysicsList {
public:
    HVeVPhysicsList();
    ~HVeVPhysicsList();

    void ConstructParticle();

    void SetCuts();

    void ConstructProcess();

private:
    G4double fCutForGamma;
    G4double fCutForElectron;
    G4double fCutForPositron;

};

#endif
