// 2020/07/15
//
#ifndef EventAction_h
#define EventAction_h 1

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4UserEventAction.hh"
#include "G4VTrajectory.hh"
#include "G4Polyline.hh"
#include "G4Polymarker.hh"
#include "G4Colour.hh"

#include <vector>

#include "globals.hh"

class EventAction : public G4UserEventAction
{
public:
	EventAction(RunAction*, PrimaryGeneratorAction*);
	~EventAction();

	void BeginOfEventAction(const G4Event*);
	void EndOfEventAction  (const G4Event*);

	void TraceTrajectory(G4VTrajectory*, G4Polyline*, G4Polymarker*, G4Polymarker*);
	void SetColour(G4Colour&, G4String);

	//
	// original
	//
	inline void  SetEventID(G4int EventID) {fEventID = EventID;};
	inline G4int GetEventID()              {return fEventID;};

	void SetEne(G4double e, G4double x, G4double y, G4double z);
	void RecCap(G4int  tID, G4double x, G4double y, G4double z, G4double t);
	void AddEne(G4double e, G4double x, G4double y, G4double z);
	void AddChE(G4double e, G4double x, G4double y, G4double z);
	void AddLos(G4double e);

private:
	RunAction*              fRunAction;
	PrimaryGeneratorAction* fPrimaryGeneratorAction;
	G4int                   fEventID;

	G4double  fEnergyIn    ;
	G4double  fPositionInX ;
	G4double  fPositionInY ;
	G4double  fPositionInZ ;
	G4int     fCaptureID   ;
	G4double  fPositionCapX;
	G4double  fPositionCapY;
	G4double  fPositionCapZ;
	G4double  fTimeCap     ;
	G4double  fEnergyAbs   ;
	G4double  fEnergyLos   ;
	G4double  fLengthGravit;
	G4double  fGravitX;
	G4double  fGravitY;
	G4double  fGravitZ;
	G4double  fChargedAbs;
	G4double  fChargedGravitX;
	G4double  fChargedGravitY;
	G4double  fChargedGravitZ;
};

inline void EventAction::SetEne(G4double e, G4double x, G4double y, G4double z){
	fEnergyIn    = e;
	fPositionInX = x;
	fPositionInY = y;
	fPositionInZ = z;
}

inline void EventAction::RecCap(G4int  tID, G4double x, G4double y, G4double z,G4double t){
	fCaptureID     = tID;
	fPositionCapX  =   x;
	fPositionCapY  =   y;
	fPositionCapZ  =   z;
	fTimeCap       =   t;
}

inline void EventAction::AddEne(G4double e, G4double x, G4double y, G4double z){
	fEnergyAbs    += e;
	fLengthGravit += e*sqrt( (x-fPositionInX)*(x-fPositionInX)+(y-fPositionInY)*(y-fPositionInY)+(z-fPositionInZ)*(z-fPositionInZ) );
	fGravitX      += e*(x-fPositionInX);
	fGravitY      += e*(y-fPositionInY);
	fGravitZ      += e*(z-fPositionInZ);
}
inline void EventAction::AddChE(G4double e, G4double x, G4double y, G4double z){
	fChargedAbs    += e;
	fChargedGravitX+= e*(x-fPositionInX);
	fChargedGravitY+= e*(y-fPositionInY);
	fChargedGravitZ+= e*(z-fPositionInZ);
}

inline void EventAction::AddLos(G4double e){
	fEnergyLos += e;
}

#endif
