#ifndef HVeVConfigMessenger_hh
#define HVeVConfigMessenger_hh 1

#include "G4UImessenger.hh"

class HVeVConfigManager;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

class HVeVConfigMessenger : public G4UImessenger {
    public:
        HVeVConfigMessenger(HVeVConfigManager* theData);
        virtual ~HVeVConfigMessenger();

        void SetNewValue(G4UIcommand* cmd, G4String value);

    private:
        HVeVConfigManager* theManager;
        G4UIcmdWithAString* hitsCmd;
        G4UIcmdWithAString* hitsRootfileCmd;
        G4UIcmdWithADoubleAndUnit* voltageCmd;
        G4UIcmdWithAString* primaryParticleNameCmd;
        G4UIcmdWithADoubleAndUnit* primaryParticleEnergyCmd;

    private:
        HVeVConfigMessenger(const HVeVConfigMessenger&); // Copying is forbidden
        HVeVConfigMessenger& operator=(const HVeVConfigMessenger&);

};

#endif

