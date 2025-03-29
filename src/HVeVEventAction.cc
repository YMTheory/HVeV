#include "HVeVEventAction.hh"
#include "GlobalDataManager.hh"

#include "G4Event.hh"

HVeVEventAction::HVeVEventAction()
: G4UserEventAction()
{}

void HVeVEventAction::BeginOfEventAction(const G4Event* event)
{
    G4cout << "***** Event ID " 
           << event->GetEventID()
           << G4endl; 
    GlobalDataManager::GetInstance()->ResetVariables();
   
}

void HVeVEventAction::EndOfEventAction(const G4Event*)
{
    if (GlobalDataManager::GetInstance()->GetLi7RecoilTrackID() != -1 
        and GlobalDataManager::GetInstance()->GetLi7RecoilPhononNumber() > 0)
    {
        G4cout << "Li7 nuclear recoil produces " 
               << GlobalDataManager::GetInstance()->GetLi7RecoilPhononNumber()
               << " phonons with total energy "
               << GlobalDataManager::GetInstance()->GetLi7RecoilPhononEnergy()
               << " eV."
               << G4endl;
    }
}