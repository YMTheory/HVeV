#include "HVeVRunAction.hh"
#include "HVeVAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "HVeVConfigManager.hh"

HVeVRunAction::HVeVRunAction()
: G4UserRunAction()
{
}

HVeVRunAction::~HVeVRunAction()
{
}

void HVeVRunAction::BeginOfRunAction(const G4Run* run)
{
    CreateNtuple();
    PrintRunInfo(run);
}




void HVeVRunAction::EndOfRunAction(const G4Run* run)
{
    WriteNtuple();
    PrintRunInfo(run);
}


void HVeVRunAction::CreateNtuple()
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    analysisManager->SetVerboseLevel(1);

    G4String filename = HVeVConfigManager::GetHitRootFile();
    analysisManager->OpenFile(filename);

    // Create ntuple
    analysisManager->CreateNtuple("Hits", "Hit information");
    analysisManager->CreateNtupleIColumn("eventid");
    analysisManager->CreateNtupleIColumn("trackid");
    analysisManager->CreateNtupleDColumn("hittime");
    analysisManager->CreateNtupleDColumn("Edep");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");

    analysisManager->FinishNtuple();
}

void HVeVRunAction::WriteNtuple()
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    analysisManager->Write();
    analysisManager->CloseFile();
}

void HVeVRunAction::PrintRunInfo(const G4Run* run)
{
    G4cout << "================= Run is = "
           << run->GetRunID() << " =================" << G4endl;
    G4cout << "================= Run type is = "
           << G4RunManager::GetRunManager()->GetRunManagerType() << " =================" << G4endl;
    G4cout << "================= Event to be processed = "
           << run->GetNumberOfEventToBeProcessed() << " =================" << G4endl;
    G4cout << "================= NEvent = "
           << run->GetNumberOfEvent() << " =================" << G4endl;
}