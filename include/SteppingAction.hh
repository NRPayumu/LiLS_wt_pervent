// 2019/11/05
//
#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include "fstream" // for output

class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(DetectorConstruction*, EventAction*);
	SteppingAction(DetectorConstruction*, EventAction*, G4String);
	~SteppingAction();

	void UserSteppingAction(const G4Step*);

private:
	DetectorConstruction* fDetector;
	EventAction*          fEventAction;

	std::ofstream *fOut;
};

#endif
