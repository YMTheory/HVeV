#ifndef HVeVConfigManager_hh
#define HVeVConfigManager_hh 1

#include "globals.hh"

class HVeVConfigMessenger;

class HVeVConfigManager {
    public:
        ~HVeVConfigManager();
        static HVeVConfigManager* Instance();

        static const G4String& GetHitOutput() { return Instance()->Hit_file; }
        static G4double GetVoltage() { return Instance()->voltage; }

        static void SetHitOutput(const G4String& name) 
            { Instance()->Hit_file = name; UpdateGeometry(); }
        static void SetVoltage(G4double value) 
            { Instance()->voltage = value; UpdateGeometry(); }

        static void UpdateGeometry();

    private:
        HVeVConfigManager();
        HVeVConfigManager(const HVeVConfigManager&) = delete;
        HVeVConfigManager(HVeVConfigManager&&) = delete;
        HVeVConfigManager& operator=(const HVeVConfigManager&) = delete;
        HVeVConfigManager& operator=(HVeVConfigManager&&) = delete;

        static HVeVConfigManager* theInstance;

    private:
        G4String Hit_file;
        G4double voltage;

        HVeVConfigMessenger* messenger;

};
#endif