#include "HVeVStackingAction.hh"

#include "G4Track.hh"
#include "G4Gamma.hh"
#include "G4SystemOfUnits.hh"

HVeVStackingAction::HVeVStackingAction()
{}

HVeVStackingAction::~HVeVStackingAction()
{}  


G4ClassificationOfNewTrack
HVeVStackingAction::ClassifyNewTrack(const G4Track* track)
{
  // kill 478 keV gamma from de-excitation of Li7
  if (track->GetDefinition() == G4Gamma::Definition() && track->GetKineticEnergy() > 477*keV) return fKill;
  else return fUrgent;
}
