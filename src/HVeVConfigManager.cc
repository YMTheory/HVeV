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
    voltage(getenv("HVeV_VOLTAGE")?strtod(getenv("HVeV_VOLTAGE"),0)*volt:0.),
    messenger(new HVeVConfigMessenger(this)) {;}

HVeVConfigManager::~HVeVConfigManager() {
    delete messenger; messenger=0;
}

void HVeVConfigManager::UpdateGeometry() {
    G4RunManager::GetRunManager()->ReinitializeGeometry(true);
}