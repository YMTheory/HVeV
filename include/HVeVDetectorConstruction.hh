#ifndef HVeVDetectorConstruction_h
#define HVeVDetectorConstruction_h 1

#include "CLHEP/Units/SystemOfUnits.h"
#include "G4VUserDetectorConstruction.hh"

class G4Material;
class G4VPhysicalVolume;
class G4CMPSurfaceProperty;
class G4ElectricField;
class HVeVSensitivity;

class HVeVDetectorConstruction : public G4VUserDetectorConstruction 
{
    public:
        HVeVDetectorConstruction();
        virtual ~HVeVDetectorConstruction();

    public:
        virtual G4VPhysicalVolume* Construct();

    private:
        void DefineMaterials();
        void SetupGeometry();
        void AttachPhononSensor(G4CMPSurfaceProperty* surfProp);
        void AttachField(G4LogicalVolume* lv);

    private:
        G4Material* fLiquidHelium;
        G4Material* fSilicon;
        G4Material* fAluminum;
        G4VPhysicalVolume* fWorldPhys;
        G4CMPSurfaceProperty* topSurfProp;
        G4CMPSurfaceProperty* botSurfProp;
        G4CMPSurfaceProperty* wallSurfProp;
        HVeVSensitivity*      electrodeSensitivity;

    private:
        // Geometry of silicon substrate
        G4double dp_siliconChipDimX = 10.0 * CLHEP::mm;
        G4double dp_siliconChipDimY = 10.0 * CLHEP::mm;
        G4double dp_siliconChipDimZ =  4.0 * CLHEP::mm;

        // Geometry of aluminum superconducting film
        G4double dp_aluminumFilmDimX = dp_siliconChipDimX;
        G4double dp_aluminumFilmDimY = dp_siliconChipDimY;
        G4double dp_aluminumFilmDimZ = 100 * CLHEP::nm;

        G4bool fConstructed;
        G4ElectricField* fEMField;
        // Simulation parameters:
        G4double voltage;           // voltage across the silicon substrate
        G4String outputFileName;    // output hit filename
        G4String outputRootFileName; 
};

#endif