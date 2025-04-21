#include "HVeVRunAction.hh"
#include "HVeVAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "HVeVConfigManager.hh"
#include "G4CMPConfigManager.hh"

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

    G4CMPConfigManager* cmpConfigManager = G4CMPConfigManager::Instance();
    cmpConfigManager->printConfig(std::cout);
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
    analysisManager->SetFirstNtupleId(1);
    analysisManager->CreateNtuple("Hits", "Hit information");
    analysisManager->CreateNtupleIColumn(1, "eventid");
    analysisManager->CreateNtupleIColumn(1, "trackid");
    analysisManager->CreateNtupleDColumn(1, "hittime");
    analysisManager->CreateNtupleDColumn(1, "Edep");
    analysisManager->CreateNtupleDColumn(1, "x");
    analysisManager->CreateNtupleDColumn(1, "y");
    analysisManager->FinishNtuple(1);

    G4bool primariesFlag = HVeVConfigManager::GetPrimariesFlag();
    if (primariesFlag) {
        analysisManager->CreateNtuple("PrimaryPhonon", "Primary phonon information");
        analysisManager->CreateNtupleIColumn(2, "eventid");
        analysisManager->CreateNtupleIColumn(2, "trackid");
        analysisManager->CreateNtupleIColumn(2, "parentid");
        analysisManager->CreateNtupleIColumn(2, "parentpdg");
        analysisManager->CreateNtupleDColumn(2, "energy");
        analysisManager->CreateNtupleDColumn(2, "startx");
        analysisManager->CreateNtupleDColumn(2, "starty");
        analysisManager->CreateNtupleDColumn(2, "startz");
        analysisManager->FinishNtuple(2);

        analysisManager->CreateNtuple("PrimaryCharge", "Primary charge pair information");
        analysisManager->CreateNtupleIColumn(3, "eventid");
        analysisManager->CreateNtupleIColumn(3, "trackid");
        analysisManager->CreateNtupleIColumn(3, "parentid");
        analysisManager->CreateNtupleIColumn(3, "parentpdg");
        analysisManager->CreateNtupleDColumn(3, "energy");
        analysisManager->CreateNtupleDColumn(3, "startx");
        analysisManager->CreateNtupleDColumn(3, "starty");
        analysisManager->CreateNtupleDColumn(3, "startz");
        analysisManager->FinishNtuple(3);

        analysisManager->CreateNtuple("LukePhonon", "Luke phonon information");
        analysisManager->CreateNtupleIColumn(4, "eventid");
        analysisManager->CreateNtupleIColumn(4, "trackid");
        analysisManager->CreateNtupleIColumn(4, "parentid");
        analysisManager->CreateNtupleIColumn(4, "parentpdg");
        analysisManager->CreateNtupleDColumn(4, "energy");
        analysisManager->CreateNtupleDColumn(4, "starttime");
        analysisManager->CreateNtupleDColumn(4, "startx");
        analysisManager->CreateNtupleDColumn(4, "starty");
        analysisManager->CreateNtupleDColumn(4, "startz");
        analysisManager->FinishNtuple(4);

        analysisManager->CreateNtuple("Primaries", "Primary information");
        analysisManager->CreateNtupleIColumn(5, "eventid");
        analysisManager->CreateNtupleIColumn(5, "trackid");
        analysisManager->CreateNtupleIColumn(5, "pdgcode");
        analysisManager->CreateNtupleIColumn(5, "parentid");
        analysisManager->CreateNtupleDColumn(5, "energy");
        analysisManager->CreateNtupleDColumn(5, "startx");
        analysisManager->CreateNtupleDColumn(5, "starty");
        analysisManager->CreateNtupleDColumn(5, "startz");
        analysisManager->CreateNtupleDColumn(5, "endx");
        analysisManager->CreateNtupleDColumn(5, "endy");
        analysisManager->CreateNtupleDColumn(5, "endz");
        analysisManager->FinishNtuple(5);
    }

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