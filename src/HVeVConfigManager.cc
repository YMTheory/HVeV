#include "HVeVConfigManager.hh"
#include "HVeVConfigMessenger.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include <stdlib.h>

HVeVConfigManager* HVeVConfigManager::theInstance = 0;

HVeVConfigManager* HVeVConfigManager::Instance() {
  if (!theInstance) theInstance = new HVeVConfigManager;
  return theInstance;
}

HVeVConfigManager::HVeVConfigManager()
  : Hit_file(getenv("HVeV_HIT_FILE")?getenv("HVeV_HIT_FILE"):"phonon_hits.txt"),
    Hit_root_file(getenv("HVeV_HIT_ROOT_FILE")?getenv("HVeV_HIT_ROOT_FILE"):"test.root"),
    voltage(getenv("HVeV_VOLTAGE")?strtod(getenv("HVeV_VOLTAGE"),0)*volt:0.),
    PrimaryParticleName(getenv("HVeV_PRIMARY_PARTICLE_NAME")?getenv("HVeV_PRIMARY_PARTICLE_NAME"):"e-"),
    PrimaryParticleEnergy(getenv("HVeV_PRIMARY_PARTICLE_ENERGY")?strtod(getenv("HVeV_PRIMARY_PARTICLE_ENERGY"),0)*eV:1.*eV),
    messenger(new HVeVConfigMessenger(this)) {;}

HVeVConfigManager::~HVeVConfigManager() {
    delete messenger; messenger=0;
}

void HVeVConfigManager::UpdateGeometry() {
    G4RunManager::GetRunManager()->ReinitializeGeometry(true);
}