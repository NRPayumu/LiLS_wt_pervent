#include "G4RunManager.hh"
#include "G4UImanager.hh"

const G4String Detector_symbolic_Name = "Gd-LS";

//const G4String Particle_Name = "gamma";
//const G4String Particle_Name = "neutron";
const G4String Particle_Name = "e+";
//const G4String Particle_Name = "fast_neutron";

const G4double Gd_fractionmass = 0.5;

//const G4double GdLS_density = 0.865 *g/cm3;
//const G4double GdLS_density = 0.860 *g/cm3;  //0.9w% 0.859941
//const G4double GdLS_density = 0.859 *g/cm3;  //0.8w% 0.859168
//const G4double GdLS_density = 0.858 *g/cm3;  //0.7w% 0.858397
//const G4double GdLS_density = 0.858 *g/cm3;  //0.6w% 0.857627
const G4double GdLS_density = 0.857 *g/cm3;  //0.5w%
//const G4double GdLS_density = 0.856 *g/cm3;  //0.4w% 0.856092
//const G4double GdLS_density = 0.855 *g/cm3;  //0.3w% 0.855326
//const G4double GdLS_density = 0.855 *g/cm3;  //0.2w% 0.85456
//const G4double GdLS_density = 0.854 *g/cm3;  //0.1w% 0.85379
//const G4double GdLS_density = 0.861 *g/cm3;  //1.0w%

//const G4double worldBoxSizeXY    = 20.0 *cm; // *cm
//const G4double worldBoxSizeZ     = 20.0 *cm;
const G4double worldBoxSizeXY    =20.0 *cm; // *cm
const G4double worldBoxSizeZ     =20.0 *cm;

// GdLS
//const G4double GdLSSizeX           = 20.0 *cm; // *cm  //Primary and DetConst
//const G4double GdLSSizeY           = 20.0 *cm; //8L
//const G4double GdLSSizeZ           = 20.0 *cm; //1.0 *mm;
const G4double GdLSSizeX           =20.0 *cm; // *cm  //Primary and DetConst
const G4double GdLSSizeY           =20.0 *cm; //8L
const G4double GdLSSizeZ           =20.0 *cm; //1.0 *mm;

// World
//const G4double worldBoxSizeXY    = 10.0 *m;
//const G4double worldBoxSizeZ     = 10.0 *m;
//const G4double worldBoxSizeXY    = 20.0 *cm;
//const G4double worldBoxSizeZ     = 20.0 *cm;
// GdLS
/*
const G4double GdLSSizeX           = 20.0 *cm;
const G4double GdLSSizeY           = 20.0 *cm; //8L
const G4double GdLSSizeZ           = 20.0 *cm; //1.0 *mm;

const G4double GdLSSizeX           = 25.0 *cm;
const G4double GdLSSizeY           = 25.0 *cm;
const G4double GdLSSizeZ           = 25.0 *cm; //16L

const G4double GdLSSizeX           = 30.0 *cm;
const G4double GdLSSizeY           = 30.0 *cm;
const G4double GdLSSizeZ           = 30.0 *cm; //27L;

const G4double GdLSSizeX           = 35.0 *cm;
const G4double GdLSSizeY           = 35.0 *cm;
const G4double GdLSSizeZ           = 35.0 *cm; //43L

const G4double GdLSSizeX           = 40.0 *cm;
const G4double GdLSSizeY           = 40.0 *cm;
const G4double GdLSSizeZ           = 40.0 *cm; //64L

const G4double GdLSSizeX           = 45.0 *cm;
const G4double GdLSSizeY           = 45.0 *cm;
const G4double GdLSSizeZ           = 45.0 *cm; //91L

const G4double GdLSSizeX           = 50.0 *cm;
const G4double GdLSSizeY           = 50.0 *cm;
const G4double GdLSSizeZ           = 50.0 *cm; //125L

const G4double GdLSSizeX           = 55.0 *cm;
const G4double GdLSSizeY           = 55.0 *cm;
const G4double GdLSSizeZ           = 55.0 *cm; //166L

const G4double GdLSSizeX           = 60.0 *cm;
const G4double GdLSSizeY           = 60.0 *cm;
const G4double GdLSSizeZ           = 60.0 *cm; //216L

const G4double GdLSSizeX           = 1.0 *m;
const G4double GdLSSizeY           = 1.0 *m;
const G4double GdLSSizeZ           = 1.0 *m; //1000L
*/
