// 2020/07/16
//
#include "PrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4HEPEvtInterface.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"

#include "G4TransportationManager.hh" // to get CopyNo
#include "G4RandomDirection.hh"

// Am+Be generate neutron
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "sstream"
#include "fstream"
#include "string.h"
#include "iomanip"

#include "variable.h"

extern std::ifstream fPriEneIn;
//using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
	G4int n_particle = 1;
	fParticleGun = new G4ParticleGun(n_particle);

	//
	// Particle type
	//
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle("neutron"); // /*neutron*/If particle is "chargedgeantino", it mean atomic decay.
	// G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
	fParticleGun -> SetParticleDefinition(particle);

	//  beam energy  //
	fPriEneIn = new std::ifstream("N_test.dat");
}

PrimaryGeneratorAction::PrimaryGeneratorAction(G4String datFileName)
{
	G4int n_particle = 1;
	fParticleGun = new G4ParticleGun(n_particle);
	// Particle type
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle(Particle_Name);
	if(Particle_Name=="fast_neutron")particle = particleTable->FindParticle("neutron");
	fParticleGun -> SetParticleDefinition(particle);

	fPriEneIn = new std::ifstream(datFileName);
	/*double Energy = 0.025;
	string line;
	getline(fPriEneIn, line);
	istringstream(line) >> Energy;
	G4cout << line << " " << Energy << G4endl;*/
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	//
	// Beam Energy
	if (!fPriEneIn) {
		G4cerr << "Error: don't exist such a data file !" << G4endl;
		//return -1;
		//break;
		exit(1);
	}

	double Energy = 2.0;
	double Eep    = 0.2;
	double En     = 0.0001;
	std::string line;
	getline(*fPriEneIn, line);
	//G4cout << line << G4endl;
	//Energy = std::stod(line);
	std::istringstream(line) >> Energy >> Eep >> En;
	//G4cout << line << " " << Energy << G4endl;
	// set particle energy
	//fParticleGun -> SetParticleEnergy(0.025 *eV); //Thermal
	if(Particle_Name=="e+")fParticleGun -> SetParticleEnergy(Eep *MeV);
	if(Particle_Name=="neutron")fParticleGun -> SetParticleEnergy(En *keV);
	if(Particle_Name=="fast_neutron")fParticleGun -> SetParticleEnergy(1 *MeV);
	if(Particle_Name=="gamma")fParticleGun -> SetParticleEnergy(2 *MeV);
	//fParticleGun -> SetParticleEnergy(0 *eV);

	//
	// Position
	//
	G4double x = 0;
	G4double y = 0;
	G4double z = 0;
	/*
	const G4double GdLSSizeX           = 20.0 ;
	const G4double GdLSSizeY           = 20.0 ;
	const G4double GdLSSizeZ           = 20.0 ; //1.0 *mm;
	*/
	//  G4double worldZHalfLength = 0;
	G4LogicalVolume* worlLV
	= G4LogicalVolumeStore::GetInstance()->GetVolume("World");
	G4Box* worldBox = 0;
	if ( worlLV) worldBox = dynamic_cast< G4Box*>(worlLV->GetSolid());
	if ( worldBox ) {
		//    worldZHalfLength = worldBox->GetZHalfLength();
	}
	else  {
		G4ExceptionDescription msg;
		msg << "World volume of box not found." << G4endl;
		msg << "Perhaps you have changed geometry." << G4endl;
		msg << "The gun will be place in the center.";
		G4Exception("B4PrimaryGeneratorAction::GeneratePrimaries()",
		"Code0002", JustWarning, msg);
	}

	x = (1.0 - 2.0 * G4UniformRand()) * GdLSSizeX/2; // within Plascin
	y = (1.0 - 2.0 * G4UniformRand()) * GdLSSizeY/2; // within Plascin
	z = (1.0 - 2.0 * G4UniformRand()) * GdLSSizeZ/2; // within Plascin

	fParticleGun -> SetParticlePosition(G4ThreeVector(x, y, z));
	fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(G4RandomDirection()));
	fParticleGun -> GeneratePrimaryVertex(anEvent);
}
