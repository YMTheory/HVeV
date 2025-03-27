#include "HVeVConfigMessenger.hh"
#include "HVeVConfigManager.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4SystemOfUnits.hh"

HVeVConfigMessenger::HVeVConfigMessenger(HVeVConfigManager* mgr)
    : G4UImessenger("/hvev/", "User configuration for HVeV example"),
    theManager(mgr)
    , hitsCmd(0)
    , voltageCmd(0)
    , primaryParticleNameCmd(0)
    , primaryParticleEnergyCmd(0)
{
    hitsCmd = CreateCommand<G4UIcmdWithAString>("HitsFile",
        "Set filename for output of phonon hit locations");
    
    voltageCmd = CreateCommand<G4UIcmdWithADoubleAndUnit>("voltage",
        "Set voltage for uniform electric field");
    voltageCmd->SetUnitCategory("Electric potential");

    primaryParticleNameCmd = CreateCommand<G4UIcmdWithAString>("PrimaryParticleName",
        "Set name of primary particle");
    
    primaryParticleEnergyCmd = CreateCommand<G4UIcmdWithADoubleAndUnit>("PrimaryParticleEnergy",
        "Set energy of primary particle");
}

HVeVConfigMessenger::~HVeVConfigMessenger() {
    delete hitsCmd; hitsCmd = 0;
    delete voltageCmd; voltageCmd = 0;
    delete primaryParticleNameCmd; primaryParticleNameCmd = 0;
    delete primaryParticleEnergyCmd; primaryParticleEnergyCmd = 0;
}

void HVeVConfigMessenger::SetNewValue(G4UIcommand* cmd, G4String value) {
    if (cmd == hitsCmd) theManager->SetHitOutput(value);

    if (cmd == voltageCmd) theManager->SetVoltage(voltageCmd->GetNewDoubleValue(value));

    if (cmd == primaryParticleNameCmd) theManager->SetPrimaryParticleName(value);

    if (cmd == primaryParticleEnergyCmd) theManager->SetPrimaryParticleEnergy(primaryParticleEnergyCmd->GetNewDoubleValue(value)/eV);
}