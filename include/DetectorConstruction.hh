// 2019/11/05
//
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

class G4Box;
class G4Tubs;
class G4Trd;
class G4LogicalVolume;
class G4Material;//
class G4SubtractionSolid;
class G4SubtractionSolid;

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4Colour.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	~DetectorConstruction();

	G4VPhysicalVolume* Construct();
	void DefineMaterials();

private:

	//
	// Material
	//
	G4Material* fWorldMaterial;               // world's material
	G4Material* fPlascinMaterial;             // Plastic scintillator's material
	G4Material* fPolybloMaterial;             // Polyethylene Block's material
	G4Material* fWaterMaterial;               // TEST-Water material
	G4Material* fBeMaterial;                  // TEST-Be    material
	G4Material* fGAGGMaterial;                // GAGG material
	G4Material* fLSMaterial;                  // LS material
	G4Material* fGeMaterial;                  // Ge material
	G4Material* fFeMaterial;                  // Fe material
	G4Material* fGdLSMaterial;
	G4Material* fLiLSMaterial;
	//
	// Colour
	//
	G4Colour white;
	G4Colour grey;
	G4Colour red;
	G4Colour green;
	G4Colour blue;
	G4Colour yellow;
};

#endif
