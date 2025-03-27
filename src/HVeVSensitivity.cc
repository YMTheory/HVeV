#include "HVeVSensitivity.hh"
#include "G4CMPElectrodeHit.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4PhononLong.hh"
#include "G4PhononTransFast.hh"
#include "G4PhononTransSlow.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "HVeVConfigManager.hh"
#include "HVeVAnalysis.hh"
#include <fstream>

HVeVSensitivity::HVeVSensitivity(G4String name) :
  G4CMPElectrodeSensitivity(name), fileName("") {
  SetOutputFile(HVeVConfigManager::GetHitOutput());
}

HVeVSensitivity::~HVeVSensitivity() {
  if (output.is_open()) output.close();
  if (!output.good()) {
    G4cerr << "Error closing output file, " << fileName << ".\n"
           << "Expect bad things like loss of data.";
  }
}

void HVeVSensitivity::EndOfEvent(G4HCofThisEvent* HCE) {
  G4int HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);
  auto* hitCol = static_cast<G4CMPElectrodeHitsCollection*>(HCE->GetHC(HCID));
  std::vector<G4CMPElectrodeHit*>* hitVec = hitCol->GetVector();

  G4RunManager* runMan = G4RunManager::GetRunManager();
  auto analysisManager = G4AnalysisManager::Instance();

  for (G4CMPElectrodeHit* hit : *hitVec) {
      analysisManager->FillNtupleIColumn(0, runMan->GetCurrentEvent()->GetEventID());
      analysisManager->FillNtupleIColumn(1, hit->GetTrackID());
      analysisManager->FillNtupleDColumn(2, hit->GetFinalTime()/ns);
      analysisManager->FillNtupleDColumn(3, hit->GetEnergyDeposit()/eV);
      analysisManager->FillNtupleDColumn(4, hit->GetFinalPosition().getX()/mm);
      analysisManager->FillNtupleDColumn(5, hit->GetFinalPosition().getY()/mm);
      analysisManager->AddNtupleRow();

  }

  //if (output.good()) {
  //  for (G4CMPElectrodeHit* hit : *hitVec) {

  //    output << runMan->GetCurrentRun()->GetRunID() << ','
  //           << runMan->GetCurrentEvent()->GetEventID() << ','
  //           << hit->GetTrackID() << ','
  //           << hit->GetParticleName() << ','
  //           << hit->GetStartEnergy()/eV << ','
  //           << hit->GetStartPosition().getX()/m << ','
  //           << hit->GetStartPosition().getY()/m << ','
  //           << hit->GetStartPosition().getZ()/m << ','
  //           << hit->GetStartTime()/ns << ','
  //           << hit->GetEnergyDeposit()/eV << ','
  //           << hit->GetWeight() << ','
  //           << hit->GetFinalPosition().getX()/m << ','
  //           << hit->GetFinalPosition().getY()/m << ','
  //           << hit->GetFinalPosition().getZ()/m << ','
  //           << hit->GetFinalTime()/ns << '\n';
  //  }
  //}
}


void HVeVSensitivity::SetOutputFile(const G4String &fn) {
    G4cout << "Not output txt file for now." << G4endl;
    //if (fileName != fn) {
    //    if (output.is_open()) output.close();
    //    fileName = fn;
    //    output.open(fileName, std::ios::app);
    //    if (!output.good()) {
    //        G4ExceptionDescription msg;
    //        msg << "Error opening output file, " << fileName << ".\n";
    //        G4Exception("HVeVSensitivity::SetOutputFile", "HVeVError", 
    //                    FatalException, msg);
    //        output.close();
    //    } else {
    //            output << "Run ID,Event ID,Track ID,Particle Name,Start Energy [eV],"
    //                   << "Start X [m],Start Y [m],Start Z [m],Start Time [ns],"
    //                   << "Energy Deposited [eV],Track Weight,End X [m],End Y [m],End Z [m],"
    //                   << "Final Time [ns]\n";
    //    }
    //}
}

G4bool HVeVSensitivity::IsHit(const G4Step* step,
                              const G4TouchableHistory*) const {
    const G4Track* track = step->GetTrack();
    const G4StepPoint* postStepPoint = step->GetPostStepPoint();
    const G4ParticleDefinition* particle = track->GetDefinition();

    G4bool correctParticle = particle == G4PhononLong::Definition() ||
                             particle == G4PhononTransFast::Definition() ||
                             particle == G4PhononTransSlow::Definition();

    G4bool correctStatus = step->GetTrack()->GetTrackStatus() == fStopAndKill &&
                           postStepPoint->GetStepStatus() == fGeomBoundary &&
                           step->GetNonIonizingEnergyDeposit() > 0.;

    return correctParticle && correctStatus;

}