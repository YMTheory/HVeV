#include "HVeVTrackingAction.hh"

#include "G4Track.hh"
#include "G4StepStatus.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4VProcess.hh"

HVeVTrackingAction::HVeVTrackingAction()
:G4UserTrackingAction()
{ }

void HVeVTrackingAction::PreUserTrackingAction(const G4Track* track)
{
    G4String name              = track->GetDefinition()->GetParticleName();
    G4double energy            = track->GetKineticEnergy()/eV;  
    G4ThreeVector pretrackpos  = track->GetPosition();
    G4double pretrack_x        = pretrackpos.getX()/mm; 
    G4double pretrack_y        = pretrackpos.getY()/mm;
    G4double pretrack_z        = pretrackpos.getZ()/mm;
    G4int trackID              = track->GetTrackID();
    G4int parentID             = track->GetParentID();

    if (parentID == 0) {
        G4cout << "Primary TrackID " << trackID << " "
               << name << " "
               << energy << " "
               << pretrack_x << " "
               << pretrack_y << " "
               << pretrack_z << " "
               << G4endl;
    }

}

void HVeVTrackingAction::PostUserTrackingAction(const G4Track* track)
{
    G4StepStatus stauts = track->GetStep()->GetPostStepPoint()->GetStepStatus();
}