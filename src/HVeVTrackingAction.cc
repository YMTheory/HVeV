#include "HVeVTrackingAction.hh"

#include "G4Track.hh"
#include "G4StepStatus.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4VProcess.hh"
#include "G4TrackingManager.hh"
#include "G4ParticleDefinition.hh"
#include "HVeVAnalysis.hh"

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
    const  G4VProcess* creator = track->GetCreatorProcess();

    if (name != "phononL" and name != "phononTS" and name != "phononTF" 
        and name != "G4CMPDriftElectron" and name != "G4CMPDriftHole") {
        if (creator) {
            G4cout << "Creator process: " << creator->GetProcessName() << G4endl;
        }
        G4cout << "Primaries track ID " << trackID << " "
               << name << " "
               << energy << " eV "
               << pretrack_x << " "
               << pretrack_y << " "
               << pretrack_z << " mm"
               << G4endl;
            
    }

    
    // Set tracks to be visualized
    if (trackID < 40) {
    //if (track->GetParentID() == 0 or track->GetParentID() == 1 or track->GetParentID() == 2) {
        fpTrackingManager->SetStoreTrajectory(true);
    } else {
        fpTrackingManager->SetStoreTrajectory(false);
    }

}

void HVeVTrackingAction::PostUserTrackingAction(const G4Track* track)
{
    G4StepStatus stauts = track->GetStep()->GetPostStepPoint()->GetStepStatus();
    G4String name              = track->GetDefinition()->GetParticleName();
    G4double energy            = track->GetKineticEnergy()/eV;  
    G4ThreeVector pretrackpos  = track->GetPosition();
    G4double pretrack_x        = pretrackpos.getX()/mm; 
    G4double pretrack_y        = pretrackpos.getY()/mm;
    G4double pretrack_z        = pretrackpos.getZ()/mm;
    G4int trackID              = track->GetTrackID();
    G4int parentID             = track->GetParentID();
    if (parentID == 0) {
        G4cout << "Primary postTracking TrackID " << trackID << " "
               << name << " "
               << energy << " eV "
               << pretrack_x << " "
               << pretrack_y << " "
               << pretrack_z << " mm"
               << G4endl;
    }
}
