// 2020/01/08
//
#include "DetectorConstruction.hh"

#include "G4Material.hh"
//#include "G4Isotope.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4UnionSolid.hh"
#include "G4EllipticalTube.hh"

#include "G4SDManager.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"

#include "G4SystemOfUnits.hh"
//
#include <iomanip>
#include <math.h>

#include "variable.h"

using namespace std;

DetectorConstruction::DetectorConstruction()
{
	//
	// define material
	//
	DefineMaterials();

	fWorldMaterial    = G4Material::GetMaterial("G4_AIR");
	fGdLSMaterial     = G4Material::GetMaterial("GdLS");
	fLiLSMaterial     = G4Material::GetMaterial("LiLS");

	// colour
	white   = G4Colour(1.0,  1.0,  1.0);
	grey    = G4Colour(0.5,  0.5,  0.5);
	red     = G4Colour(1.0,  0.0,  0.0);
	green   = G4Colour(0.0,  1.0,  0.0);
	blue    = G4Colour(0.0,  0.0,  1.0);
	yellow  = G4Colour(1.0,  1.0,  0.0);
}

DetectorConstruction::~DetectorConstruction()
{;}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	//
	// visibility flag
	//
	G4bool visFlagWorld    = 1; // white
	G4bool visFlagGdLS        = 1; //red
	G4bool visFlagLiLS        = 1; //red

	//
	// copy number
	//
	G4int copyNoWorld      = 9;
	G4int copyNoGdLS         = 301;
	G4int copyNoLiLS         = 401;

	//
	// Geometory parameters
	//

	// geometory parameter values

	// World ////////////////////
	G4Box*             worldSolid    = new G4Box("World", worldBoxSizeXY / 2.0, worldBoxSizeXY / 2.0, worldBoxSizeZ / 2.0);
	G4LogicalVolume*   worldLogical  = new G4LogicalVolume(worldSolid, fWorldMaterial, "World");
	G4VPhysicalVolume* worldPhysical = new G4PVPlacement(0, G4ThreeVector(), worldLogical, "World", 0, false, copyNoWorld);
	G4VisAttributes* worldVisAtt = new G4VisAttributes(grey);
	worldVisAtt  -> SetVisibility(visFlagWorld);
	worldLogical -> SetVisAttributes(worldVisAtt);

	// GdLS /////////////
	// Mother = World
	/*G4Box*GdLSSolid   = new G4Box("GdLS", GdLSSizeX / 2.0, GdLSSizeY / 2.0, GdLSSizeZ / 2.0);
	G4LogicalVolume*   GdLSLogical = new G4LogicalVolume(GdLSSolid, fGdLSMaterial, "GdLS");
	G4double GdLSPositionZ = 0*cm;
	new G4PVPlacement(0, G4ThreeVector(0,0,GdLSPositionZ), GdLSLogical, "GdLS", worldLogical, false, copyNoGdLS);
	G4VisAttributes* GdLSVisAtt = new G4VisAttributes(red);
	GdLSVisAtt  -> SetVisibility(visFlagGdLS);
	GdLSLogical -> SetVisAttributes(GdLSVisAtt);*/

	// LiLS /////////////
	// Mother = World
	G4Box*LiLSSolid   = new G4Box("LiLS", GdLSSizeX / 2.0, GdLSSizeY / 2.0, GdLSSizeZ / 2.0);
	G4LogicalVolume*   LiLSLogical = new G4LogicalVolume(LiLSSolid, fLiLSMaterial, "LiLS");
	G4double LiLSPositionZ = 0*cm;
	new G4PVPlacement(0, G4ThreeVector(0,0,LiLSPositionZ), LiLSLogical, "LiLS", worldLogical, false, copyNoLiLS);
	G4VisAttributes* LiLSVisAtt = new G4VisAttributes(red);
	LiLSVisAtt  -> SetVisibility(visFlagLiLS);
	LiLSLogical -> SetVisAttributes(LiLSVisAtt);

	// always return the physical world
	return worldPhysical;
}

void DetectorConstruction::DefineMaterials()
{
	// Material defined using NIST Manager
	// http://geant4.web.cern.ch/geant4/G4UsersDocuments/UsersGuides/ForApplicationDeveloper/html/Detector/materialNames.html
	G4NistManager* nistManager = G4NistManager::Instance();
	nistManager -> FindOrBuildMaterial("G4_AIR");
	G4Material* H2O = nistManager -> FindOrBuildMaterial("G4_WATER");

	//for GdLS
	//
	// define elements
	G4Element* H   = nistManager -> FindOrBuildElement("H");
	G4Element* C    = nistManager -> FindOrBuildElement("C");
	G4Element* N   = nistManager -> FindOrBuildElement("N");
	G4Element* O    = nistManager -> FindOrBuildElement("O");
	G4Element* Gd  = nistManager -> FindOrBuildElement("Gd");
	G4Element* Li  = nistManager -> FindOrBuildElement("Li");
	G4Element* Cl  = nistManager -> FindOrBuildElement("Cl");
	G4Isotope* Li6 = new G4Isotope("Li6",3,6,0.);
	//G4Isotope https://indico.cern.ch/event/781244/contributions/3251907/attachments/1782383/2900303/Materials.pdf
	G4Element* EnrLi6 = new G4Element("EnrichedLi6","6Li",1);
	EnrLi6 -> AddIsotope(Li6, 1);

	G4double fractionmass, density;
	G4int    ncomponents, natoms;
	G4String name, symbol;

	// Materials for Lquid Scintillator //////////////////
	//
	//LAB
	//https://www.noe.jxtg-group.co.jp/business/chemical/product/alkyl_benzene.html
	//hino p71 http://www.awa.tohoku.ac.jp/Thesis/ThesisFile/hino_yota_m.pdf
	density = 0.852*g/cm3; // No data in MSDS, written in GLG4DetectorConstruction.cc
	G4Material* LAB = new G4Material("LAB", density, ncomponents = 2);
	LAB -> AddElement(C, natoms = 18);
	LAB -> AddElement(H, natoms = 30);

	//bis-MSB
	// bis-MSB (1.4-Bis(2-methylstynyl)benzene) = C24H22 !!! temporary density !!!
	density = 1.3*g/cm3; // No data in MSDS, written in GLG4DetectorConstruction.cc
	G4Material* BisMSB = new G4Material("Bis-MSB", density, ncomponents = 2);
	BisMSB -> AddElement(C, natoms = 24);
	BisMSB -> AddElement(H, natoms = 22);

	// DPO(PPO) (2.5-Diphenylozazole) C15H11NO !!! temporary density !!!
	density = 1.06 *g/cm3;  // No data in MSDS, written in GLG4DetectorConstruction.cc
	G4Material* PPO = new G4Material("PPO", density, ncomponents = 4);
	PPO -> AddElement(C, natoms = 15);
	PPO -> AddElement(H, natoms = 11);
	PPO -> AddElement(N, natoms = 1);
	PPO -> AddElement(O, natoms = 1);

	//Gd
	density =  7.9*g/cm3;  // No data in MSDS, written in GLG4DetectorConstruction.cc
	G4Material* Gd_mat = new G4Material("Gd_mat", density, ncomponents = 1);
	Gd_mat -> AddElement(Gd, natoms = 1);

	density = 0.853 *g/cm3;
	G4Material* NonGdLS = new G4Material("NonGdLS", density, ncomponents = 3);
	NonGdLS -> AddMaterial(LAB,     fractionmass = 99.6457 *perCent); //
	NonGdLS -> AddMaterial(PPO,     fractionmass =  0.3508   *perCent); // 3.0 g/l
	NonGdLS -> AddMaterial(BisMSB,  fractionmass =  0.0035 *perCent); // 30 mg/l

	G4Material* GdLS_inside = new G4Material("GdLS", GdLS_density, ncomponents = 2);
	//GdLS_inside -> AddMaterial(NonGdLS, fractionmass = 99.5 *perCent); //
	//GdLS_inside -> AddMaterial(Gd_mat,  fractionmass =  0.5 *perCent); // 0.5wt%
	GdLS_inside -> AddMaterial(NonGdLS, fractionmass = (100-Gd_fractionmass) *perCent); //
	GdLS_inside -> AddMaterial(Gd_mat,  fractionmass =      Gd_fractionmass  *perCent); //

	//PNE https://www.env.go.jp/chemi/report/h21-01/pdf/chpt1/1-2-3-10.pdf
	//PNE-9 : C_15+2n H_24+4n O_1+n n=9
	//PNE-15 : density = 1.07g/ml
	//density https://labchem-wako.fujifilm.com/sds/W01W0116-2169JGHEJP.pdf
	density = 1.06 *g/cm3;
	G4Material* PNE_9 = new G4Material("PNE_9", density, ncomponents = 3);
	PNE_9 -> AddElement(H, natoms = 60);
	PNE_9 -> AddElement(C, natoms = 33);
	PNE_9 -> AddElement(O, natoms = 10);

	density = 2.07 *g/cm3;
	G4Material* LiCl = new G4Material("LiCl", density, ncomponents = 2);
	LiCl -> AddElement(Li, natoms = 1);
	LiCl -> AddElement(Cl, natoms = 1);

	density = 2.07 *g/cm3;
	G4Material* Li6Cl = new G4Material("Li6Cl", density, ncomponents = 2);
	//Li6Cl -> AddIsotope(Li6, natoms = 1);
	Li6Cl -> AddElement(EnrLi6, natoms = 1);
	Li6Cl -> AddElement(Cl, natoms = 1);

	density = 1.09 *g/cm3;
	G4Material* LiSolution = new G4Material("LiH2O", density, ncomponents = 2);
	//LiSolution -> AddMaterial(LiCl, fractionmass = 17.15 *perCent); //10.366
	LiSolution -> AddMaterial(Li6Cl, fractionmass = 17.15 *perCent); //10.366
	LiSolution -> AddMaterial(H2O,  fractionmass = 82.85  *perCent); //50.093

	density = 0.852 *g/cm3;
	G4Material* Bis_master = new G4Material("BisMas", density, ncomponents = 2);
	Bis_master -> AddMaterial(BisMSB, fractionmass =  0.05 *perCent); //0.10
	Bis_master -> AddMaterial(LAB,  fractionmass =   99.95  *perCent); //200

	density = 0.889 *g/cm3;
	G4Material* LiLS = new G4Material("LiLS", density, ncomponents = 5);
	LiLS -> AddMaterial(LAB,  fractionmass =   74.62  *perCent); // 80
	LiLS -> AddMaterial(PPO,     fractionmass =  0.32   *perCent); // 0.348
	LiLS -> AddMaterial(Bis_master, fractionmass = 6.53 *perCent); // 7.0
	LiLS -> AddMaterial(PNE_9,  fractionmass =    15.86 *perCent); // 17.0
	LiLS -> AddMaterial(LiSolution,  fractionmass =   2.67  *perCent); // 2.86

	// Print materials
	G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
	G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}
