#include "HVeVSteppingAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "HVeVAnalysis.hh"
#include "G4RunManager.hh"

HVeVSteppingAction::HVeVSteppingAction()
{}

HVeVSteppingAction::~HVeVSteppingAction()
{}

void HVeVSteppingAction::UserSteppingAction(const G4Step* step)
{
    G4Track* track = step->GetTrack();
    G4String particleName = track->GetParticleDefinition()->GetParticleName();
    G4int trackID = track->GetTrackID();
    G4int parentID = track->GetParentID();
    G4int pdgCode = track->GetDefinition()->GetPDGEncoding();
    G4double ekin = track->GetKineticEnergy()/eV;

    G4RunManager* runMan = G4RunManager::GetRunManager();
    auto analysisManager = G4AnalysisManager::Instance();

    const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();
    if (secondaries->size() > 0) {

        //G4cout << "Primary Track ID: " << trackID << " " << particleName
        //       << " produced " << secondaries->size() << " secondaries" << G4endl;

        if (particleName != "phononL" and particleName != "phononTS" and particleName != "phononTF"
            and particleName != "G4CMPDriftElectron" and particleName != "G4CMPDriftHole") {
                G4double total_energy_charge_pair = 0.0;
                G4double total_energy_phonon = 0.0;
                G4double total_energy_others = 0.0;

                for (auto secondary : *secondaries) {
                    G4int secID = secondary->GetTrackID();
                    G4double secEkin = secondary->GetKineticEnergy()/eV;
                    G4String secName = secondary->GetParticleDefinition()->GetParticleName();
                    if (secName == "G4CMPDriftElectron" or secName == "G4CMPDriftHole") { 
                        total_energy_charge_pair += secEkin;
                        G4double x = secondary->GetPosition().x()/mm;
                        G4double y = secondary->GetPosition().y()/mm;
                        G4double z = secondary->GetPosition().z()/mm;

                        analysisManager->FillNtupleIColumn(3, 0, runMan->GetCurrentEvent()->GetEventID());
                        analysisManager->FillNtupleIColumn(3, 1, secID);
                        analysisManager->FillNtupleIColumn(3, 2, trackID);
                        analysisManager->FillNtupleIColumn(3, 3, pdgCode);
                        analysisManager->FillNtupleDColumn(3, 4, secEkin);
                        analysisManager->FillNtupleDColumn(3, 5, x);
                        analysisManager->FillNtupleDColumn(3, 6, y);
                        analysisManager->FillNtupleDColumn(3, 7, z);
                        analysisManager->AddNtupleRow(3);
                    }
                    else if (secName == "phononL" or secName == "phononTS" or secName == "phononTF") {
                        total_energy_phonon += secEkin;

                        G4double x = secondary->GetPosition().x()/mm;
                        G4double y = secondary->GetPosition().y()/mm;
                        G4double z = secondary->GetPosition().z()/mm;

                        analysisManager->FillNtupleIColumn(2, 0, runMan->GetCurrentEvent()->GetEventID());
                        analysisManager->FillNtupleIColumn(2, 1, secID);
                        analysisManager->FillNtupleIColumn(2, 2, trackID);
                        analysisManager->FillNtupleIColumn(2, 3, pdgCode);
                        analysisManager->FillNtupleDColumn(2, 4, secEkin);
                        analysisManager->FillNtupleDColumn(2, 5, x);
                        analysisManager->FillNtupleDColumn(2, 6, y);
                        analysisManager->FillNtupleDColumn(2, 7, z);
                        analysisManager->AddNtupleRow(2);

                    }
                    else {
                        total_energy_others += secEkin;
                        G4cout << "Secondary Track ID: " << secID << " " << secName << " Ekin: " << secEkin << G4endl;
                    }
                }
            G4cout << "\nTotal energy partition of " << particleName << ": " << ekin << " eV\n"
                   << "Charge-pair: " << total_energy_charge_pair << " eV\n"
                   << "Phonon: " << total_energy_phonon << " eV\n"
                   << "Others: " << total_energy_others << " eV\n" << G4endl;
        }

        if (particleName == "G4CMPDriftElectron" or particleName == "G4CMPDriftHole") {
                for (auto secondary : *secondaries) {
                    G4int secID = secondary->GetTrackID();
                    G4double secEkin = secondary->GetKineticEnergy()/eV;
                    G4String secName = secondary->GetParticleDefinition()->GetParticleName();
                    G4double x = secondary->GetPosition().x()/mm;
                    G4double y = secondary->GetPosition().y()/mm;
                    G4double z = secondary->GetPosition().z()/mm;

                    if (secName == "phononL" or secName == "phononTS" or secName == "phononTF")
                    {
                        analysisManager->FillNtupleIColumn(4, 0, runMan->GetCurrentEvent()->GetEventID());
                        analysisManager->FillNtupleIColumn(4, 1, secID);
                        analysisManager->FillNtupleIColumn(4, 2, trackID);
                        analysisManager->FillNtupleIColumn(4, 3, pdgCode);
                        analysisManager->FillNtupleDColumn(4, 4, secEkin);
                        analysisManager->FillNtupleDColumn(4, 5, x);                        
                        analysisManager->FillNtupleDColumn(4, 6, y);                        
                        analysisManager->FillNtupleDColumn(4, 7, z);                        
                        analysisManager->AddNtupleRow(4);
                    }
                }
        }
    }
}