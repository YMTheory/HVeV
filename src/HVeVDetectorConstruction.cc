#include "HVeVDetectorConstruction.hh"
#include "HVeVSensitivity.hh"
#include "HVeVConfigManager.hh"
#include "G4CMPLogicalBorderSurface.hh"
#include "G4CMPPhononElectrode.hh"
#include "G4CMPSurfaceProperty.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4GeometryManager.hh"
#include "G4LatticeLogical.hh"
#include "G4LatticeManager.hh"
#include "G4LatticePhysical.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4SolidStore.hh"
#include "G4SystemOfUnits.hh"
#include "G4TransportationManager.hh"
#include "G4Tubs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4CMPFieldManager.hh"
#include "G4CMPMeshElectricField.hh"
#include "G4UniformElectricField.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HVeVDetectorConstruction::HVeVDetectorConstruction()
  : fAluminum(0), fSilicon(0), fLiquidHelium(0),
    fWorldPhys(0), topSurfProp(0), botSurfProp(0), wallSurfProp(0),
    electrodeSensitivity(0), fConstructed(false), 
    outputFileName(""),
    fEMField(nullptr), voltage(0.) {;}

HVeVDetectorConstruction::~HVeVDetectorConstruction() {
  delete fEMField;
  delete topSurfProp;
  delete botSurfProp;
  delete wallSurfProp;
}


G4VPhysicalVolume* HVeVDetectorConstruction::Construct()
{
    if(fConstructed) {
        G4GeometryManager::GetInstance()->OpenGeometry();
        G4PhysicalVolumeStore::GetInstance()->Clean();
        G4LogicalVolumeStore::GetInstance()->Clean();
        G4SolidStore::GetInstance()->Clean();

        if (outputFileName != HVeVConfigManager::GetHitOutput()) {
        outputFileName = HVeVConfigManager::GetHitOutput();
            if (electrodeSensitivity) electrodeSensitivity->SetOutputFile(outputFileName);
        }

        if (voltage != HVeVConfigManager::GetVoltage()) {
            delete fEMField; fEMField = nullptr;
        }

        G4LatticeManager::GetLatticeManager()->Reset();

        G4CMPLogicalBorderSurface::CleanSurfaceTable();
    }

    voltage = HVeVConfigManager::GetVoltage();

    DefineMaterials();
    SetupGeometry();
    fConstructed = true;

    return fWorldPhys;
}

void HVeVDetectorConstruction::DefineMaterials()
{
    G4NistManager
        * nistManager = G4NistManager::Instance();
    fAluminum = nistManager->FindOrBuildMaterial("G4_Al");
    fSilicon = nistManager->FindOrBuildMaterial("G4_Si");
    fLiquidHelium = nistManager->FindOrBuildMaterial("G4_AIR"); // TODO: Correct this
}

void HVeVDetectorConstruction::SetupGeometry()
{
    // Set up the liquid helium world volume
    G4VSolid
        * worldSolid = new G4Box("World", 16.*cm, 16.*cm, 16.*cm);
    G4LogicalVolume* worldLogical =
        new G4LogicalVolume(worldSolid, fLiquidHelium, "World");
    worldLogical->SetUserLimits(new G4UserLimits(10*mm, DBL_MAX, DBL_MAX, 0, 0));
    fWorldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogical, "World", 0, false, 0);

    // Set up the silicon substrate
    G4VSolid
        * fSiliconSolid = new G4Box("fSiliconSolid", 
                                    dp_siliconChipDimX/2., 
                                    dp_siliconChipDimY/2., 
                                    dp_siliconChipDimZ/2.);

    G4LogicalVolume* fSiliconLogical = 
        new G4LogicalVolume(fSiliconSolid, fSilicon, "fSiliconLogical");
    G4VPhysicalVolume* SiPhys =
        new G4PVPlacement(0, G4ThreeVector(), fSiliconLogical, "fSiliconPhysical",
                          worldLogical, false, 0);
    // Set up lattice properties for silicon
    G4LatticeManager* LM = G4LatticeManager::GetLatticeManager();
    G4LatticeLogical* SiLogical = LM->LoadLattice(fSilicon, "Si");
    G4LatticePhysical* SiPhysical = new G4LatticePhysical(SiLogical);
    SiPhysical->SetMillerOrientation(1, 0, 0);
    LM->RegisterLattice(SiPhys, SiPhysical);
    
    // Set up the aluminum superconducting thin films
    G4VSolid* fAluminumSolid = new G4Box("aluminiumSolid",
                                        dp_aluminumFilmDimX/2.,
                                        dp_aluminumFilmDimY/2.,
                                        dp_aluminumFilmDimZ/2.
                                    );
    G4LogicalVolume* fAluminumLogical =
        new G4LogicalVolume(fAluminumSolid, fAluminum, "fAluminumLogical");
    G4VPhysicalVolume* aluminumTopPhysical = new G4PVPlacement(0,
                                                            G4ThreeVector(0., 0., (dp_siliconChipDimZ+dp_aluminumFilmDimZ)/2.),
                                                            fAluminumLogical,
                                                            "fAluminumPhysical",
                                                            worldLogical,
                                                            false,
                                                            0);
    G4VPhysicalVolume* aluminumBotPhysical = new G4PVPlacement(0,
                                                            G4ThreeVector(0., 0., -(dp_siliconChipDimZ+dp_aluminumFilmDimZ)/2.),
                                                            fAluminumLogical,
                                                            "fAluminumPhysical",
                                                            worldLogical,
                                                            false,
                                                            1);
    // detector -- Note: "sensitive detector" is atttached to the silicon substrate
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    if (!electrodeSensitivity) {
        electrodeSensitivity = new HVeVSensitivity("Electrode");
        SDman->AddNewDetector(electrodeSensitivity);
        fSiliconLogical->SetSensitiveDetector(electrodeSensitivity);
    }
    
    // Set up the electric field across the silicon substrate
    // AttachField(fSiliconLogical);

    if (!fConstructed) {
        const G4double GHz = 1e9 * hertz;
        const std::vector<G4double> anhCoeffs = {0, 0, 0, 0, 0, 1.51e-14};
        const std::vector<G4double> diffCoeffs =
          {5.88e-2, 7.83e-4, -2.47e-6, 1.71e-8, -2.98e-11};
        const std::vector<G4double> specCoeffs =
          {0,928, -2.03e-4, -3.21e-6, 3.1e-9, 2.9e-13};

        const G4double anhCutoff = 520., reflCutoff = 350.;   // Units external

        topSurfProp = new G4CMPSurfaceProperty("TopAlSurf", 1.0, 0.0, 0.0, 0.0, // the first 4 entries deal with e/h absorption and reflection
    					  	        0.3, 1.0, 0.0, 0.0); // the last 4 entries deal with phonon absorption and reflection, [absorption, reflection, specular reflection ratio, ...]
        topSurfProp->AddScatteringProperties(anhCutoff, reflCutoff, anhCoeffs,
    					 diffCoeffs, specCoeffs, GHz, GHz, GHz);
        AttachPhononSensor(topSurfProp);

        botSurfProp = new G4CMPSurfaceProperty("BotAlSurf", 1.0, 0.0, 0.0, 0.0,
    					   	        0.3, 1.0, 0.0, 0.0);
        botSurfProp->AddScatteringProperties(anhCutoff, reflCutoff, anhCoeffs,
    					 diffCoeffs, specCoeffs, GHz, GHz, GHz);
        AttachPhononSensor(botSurfProp);

        wallSurfProp = new G4CMPSurfaceProperty("WallSurf", 0.0, 1.0, 0.0, 0.0,
    					    	          0.0, 1.0, 0.0, 0.0);
        wallSurfProp->AddScatteringProperties(anhCutoff, reflCutoff, anhCoeffs,
					  diffCoeffs, specCoeffs, GHz, GHz,GHz);

    }

    new G4CMPLogicalBorderSurface("detTop", SiPhys, aluminumTopPhysical,
		    		topSurfProp);
    new G4CMPLogicalBorderSurface("detBot", SiPhys, aluminumBotPhysical,
		    		botSurfProp);
    new G4CMPLogicalBorderSurface("detWall", SiPhys, fWorldPhys,
		    		wallSurfProp);

    //                                        
    // Visualization attributes
    //
    worldLogical->SetVisAttributes(G4VisAttributes::Invisible);
    G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    simpleBoxVisAtt->SetVisibility(true);
    fSiliconLogical->SetVisAttributes(simpleBoxVisAtt);
    fAluminumLogical->SetVisAttributes(simpleBoxVisAtt);
}

void HVeVDetectorConstruction::
AttachPhononSensor(G4CMPSurfaceProperty* surfProp)
{
    if (!surfProp) return;

    auto sensorProp = surfProp->GetPhononMaterialPropertiesTablePointer();
    sensorProp->AddConstProperty("filmAbsorption", 0.20);    // True sensor area
    sensorProp->AddConstProperty("filmThickness", 600.*nm);
    sensorProp->AddConstProperty("gapEnergy", 173.715e-6*eV);
    sensorProp->AddConstProperty("lowQPLimit", 3.);
    sensorProp->AddConstProperty("phononLifetime", 242.*ps);
    sensorProp->AddConstProperty("phononLifetimeSlope", 0.29);
    sensorProp->AddConstProperty("vSound", 3.26*km/s);
    sensorProp->AddConstProperty("subgapAbsorption", 0.1);

    // Attach electrode object to handle KaplanQP interface
    surfProp->SetPhononElectrode(new G4CMPPhononElectrode);
}

void HVeVDetectorConstruction::AttachField(G4LogicalVolume* lv)
{
    if (!fEMField) {
        G4double fieldMag = -voltage / dp_siliconChipDimZ;
        fEMField = new G4UniformElectricField(G4ThreeVector(0., 0., fieldMag));
    }
    if (!lv->GetFieldManager()) {
        G4FieldManager* fFieldMgr = new G4CMPFieldManager(fEMField);
        lv->SetFieldManager(fFieldMgr, true);
    }
    lv->GetFieldManager()->SetDetectorField(fEMField);
}