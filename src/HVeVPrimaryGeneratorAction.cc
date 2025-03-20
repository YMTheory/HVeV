#include "HVeVPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4Geantino.hh"
#include "G4RandomDirection.hh"
#include "G4PhononTransFast.hh"
#include "G4PhononTransSlow.hh"
#include "G4PhononLong.hh"
#include "G4CMPDriftElectron.hh"
#include "G4CMPDriftHole.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"

using namespace std;

HVeVPrimaryGeneratorAction::HVeVPrimaryGeneratorAction() { 
    fParticleGPS = new G4GeneralParticleSource();
}

HVeVPrimaryGeneratorAction::~HVeVPrimaryGeneratorAction() {
    delete fParticleGPS;
}

void HVeVPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    fParticleGPS->GeneratePrimaryVertex(anEvent);
}