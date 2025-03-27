#include "HVeVPrimaryGeneratorAction.hh"
#include "HVeVConfigManager.hh"

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

    G4String f_primaryParticleName = HVeVConfigManager::GetPrimaryParticleName();
    G4double f_primaryParticleEnergy = HVeVConfigManager::GetPrimaryParticleEnergy();

    if (f_primaryParticleName == "chargepair") {
        // Generate Drift Electron:
        fParticleGPS->SetParticleDefinition(G4CMPDriftElectron::Definition());
        // Set the energy for the drift electron
        fParticleGPS->GetCurrentSource()->GetEneDist()->SetEnergyDisType("Mono");
        fParticleGPS->GetCurrentSource()->GetEneDist()->SetMonoEnergy(f_primaryParticleEnergy * eV);
        // Set the position of the drift electron
        fParticleGPS->GetCurrentSource()->GetPosDist()->SetPosDisType("Point");
        fParticleGPS->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0.0, 0.0, 0.0));
        // Set the angular distribution of the drift electron
        fParticleGPS->GetCurrentSource()->GetAngDist()->SetAngDistType("iso");
        // Generate the drift electron
        fParticleGPS->GeneratePrimaryVertex(anEvent);

        // Generate Drift Hole:
        fParticleGPS->SetParticleDefinition(G4CMPDriftHole::Definition());
        // Set the energy for the drift hole
        fParticleGPS->GetCurrentSource()->GetEneDist()->SetEnergyDisType("Mono");
        fParticleGPS->GetCurrentSource()->GetEneDist()->SetMonoEnergy(f_primaryParticleEnergy * eV);
        // Set the position of the drift hole
        fParticleGPS->GetCurrentSource()->GetPosDist()->SetPosDisType("Point");
        fParticleGPS->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0.0, 0.0, 0.0));
        // Set the angular distribution of the drift hole
        fParticleGPS->GetCurrentSource()->GetAngDist()->SetAngDistType("iso");
        // Generate the drift hole
        fParticleGPS->GeneratePrimaryVertex(anEvent);
    
    }

    else {
        fParticleGPS->GeneratePrimaryVertex(anEvent);
    }
}