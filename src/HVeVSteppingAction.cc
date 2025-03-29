#include "HVeVSteppingAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"

HVeVSteppingAction::HVeVSteppingAction()
{}

HVeVSteppingAction::~HVeVSteppingAction()
{}

void HVeVSteppingAction::UserSteppingAction(const G4Step* step)
{
    G4Track* track = step->GetTrack();
    G4int trackID = track->GetTrackID();
    G4int parentID = track->GetParentID();
    G4int pdgCode = track->GetDefinition()->GetPDGEncoding();
    G4double ekin = track->GetKineticEnergy();

    const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();
}