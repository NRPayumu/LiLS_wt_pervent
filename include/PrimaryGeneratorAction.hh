// 2019/11/05
//
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"

class G4GeneralParticleSource;
class G4ParticleGun;
class G4Event;
class G4VPrimaryGenerator;

#include "fstream"
//using namespace std;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	PrimaryGeneratorAction();
	PrimaryGeneratorAction(G4String);
	~PrimaryGeneratorAction();

	void GeneratePrimaries(G4Event* anEvent);

private:
	G4ParticleGun* fParticleGun;

	std::ifstream *fPriEneIn;
};

#endif
