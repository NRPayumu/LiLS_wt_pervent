// 2020/06/16
//
#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class HistoManager;

class RunAction : public G4UserRunAction
{
public:
	RunAction();
	RunAction(G4String);
	~RunAction();

	void BeginOfRunAction(const G4Run*);
	//void BeginOfRunAction(const G4Run* ,G4String);
	void EndOfRunAction(const G4Run*);

private:
	G4int    fEventID;
	G4double fEnergyDeposit;
};

#endif
