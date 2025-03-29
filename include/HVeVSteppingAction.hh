#ifndef HVeVSteppingAction_hh
#define HVeVSteppingAction_hh 1

#include "G4UserSteppingAction.hh"

class HVeVSteppingAction : public G4UserSteppingAction
{
    public:
        HVeVSteppingAction();
        virtual ~HVeVSteppingAction();

        virtual void UserSteppingAction(const G4Step*);

};

#endif