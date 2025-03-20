#include "HVeVEventAction.hh"

#include "G4Event.hh"

HVeVEventAction::HVeVEventAction()
: G4UserEventAction()
{}

void HVeVEventAction::BeginOfEventAction(const G4Event* event)
{
    G4cout << "***** Event ID " 
           << event->GetEventID()
           << G4endl; 
}

void HVeVEventAction::EndOfEventAction(const G4Event*)
{}