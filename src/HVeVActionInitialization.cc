
#include "HVeVActionInitialization.hh"
#include "HVeVPrimaryGeneratorAction.hh"
#include "G4CMPStackingAction.hh"

#include "HVeVEventAction.hh"

void HVeVActionInitialization::Build() const {
  SetUserAction(new HVeVPrimaryGeneratorAction);
  SetUserAction(new G4CMPStackingAction);
  SetUserAction(new HVeVEventAction());
} 
