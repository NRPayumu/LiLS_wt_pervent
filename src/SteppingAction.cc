// 2020/07/17
//
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4SteppingManager.hh"

#include "G4Track.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
#include "G4RunManager.hh"
#include <iomanip>

extern std::ofstream fOut;

SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* evt)
:fDetector(det), fEventAction(evt)
{
	fOut = new std::ofstream("data_step.dat");
}

SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* evt, G4String datFileName)
:fDetector(det), fEventAction(evt)
{
	fOut = new std::ofstream(datFileName);
}

SteppingAction::~SteppingAction()
{;}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
//void SteppingAction::UserSteppingAction(const G4Step*)
{
	// Step ---> pre/postStepPoint
	//
	G4StepPoint* preStepPoint  = aStep -> GetPreStepPoint();
	G4StepPoint* postStepPoint = aStep -> GetPostStepPoint();

	// preStepPoint
	G4String materialName;
	if (preStepPoint -> GetPhysicalVolume() != NULL)
	materialName = preStepPoint -> GetPhysicalVolume() -> GetName(); // should be pre
	else
	materialName = "NULL";

	// get process name
	//
	G4String preProcessName;
	if (preStepPoint -> GetProcessDefinedStep() != NULL)
	preProcessName = preStepPoint -> GetProcessDefinedStep() -> GetProcessName();
	else
	preProcessName = "UserLimit";

	G4String postProcessName;
	if (postStepPoint -> GetProcessDefinedStep() != NULL)
	postProcessName = postStepPoint -> GetProcessDefinedStep() -> GetProcessName();
	else
	postProcessName = "UserLimit";

	// Track
	G4Track* aTrack              = aStep -> GetTrack();

	const G4VProcess*  process   = aTrack -> GetCreatorProcess();
	G4String originedProcessName;
	if (process != 0)
	originedProcessName = process -> GetProcessName();
	else
	originedProcessName = "UserLimit";

	G4ParticleDefinition* parDef = aTrack -> GetDefinition();
	G4int PDGNumber              = parDef -> GetPDGEncoding();
	G4String particleName        = parDef -> GetParticleName();

	G4double EveID = fEventAction -> GetEventID();
	G4double ParID = aTrack -> GetParentID();
	G4double TraID = aTrack -> GetTrackID();
	G4String NowPV = preStepPoint -> GetPhysicalVolume() -> GetName();
	G4int    CopyN = aStep  -> GetPreStepPoint()  -> GetTouchableHandle() -> GetCopyNumber();
	G4double PrePX = preStepPoint  -> GetPosition()[0];
	G4double PrePY = preStepPoint  -> GetPosition()[1];
	G4double PrePZ = preStepPoint  -> GetPosition()[2];
	G4double PosPX = postStepPoint -> GetPosition()[0];
	G4double PosPY = postStepPoint -> GetPosition()[1];
	G4double PosPZ = postStepPoint -> GetPosition()[2];
	G4double OriEn = aTrack -> GetVertexKineticEnergy();
	G4double CurEn = aTrack -> GetKineticEnergy();
	G4double StDep = aStep  -> GetTotalEnergyDeposit();
	G4double GTime = postStepPoint -> GetGlobalTime() / second;

	if(TraID==1 && preProcessName=="UserLimit"){
		fEventAction->SetEne(OriEn,PrePX,PrePY,PrePZ);
		//fEventAction->AddEne(OriEn);
	}
	if(postProcessName=="nCapture" && CopyN == 401){
		fEventAction->RecCap(ParID,PosPX,PosPY,PosPZ,GTime);
	}
	/*if(TraID==1 && CopyN == 301 && (postProcessName=="annihil" || postProcessName=="nCapture")){
		fEventAction->RecCap(ParID,PosPX,PosPY,PosPZ,GTime);
		//fEventAction->AddEne(OriEn);
	}*/
	/*if(preProcessName=="Transportation" && CopyN == 9){
		//fEventAction->AddEne(-1*CurEn));
		fEventAction->AddLos(CurEn);
	}*/
	if(postProcessName=="Transportation" && CopyN == 401){
		//fEventAction->AddEne(-1*CurEn));
		fEventAction->AddLos(CurEn);
	}
	if(CopyN == 401){
		if( particleName != "proton" ){
			fEventAction->AddEne(StDep,PosPX,PosPY,PosPZ);
		}
		//if( particleName == "e-" || particleName == "e+" || particleName == "proton" || particleName == "mu-" || particleName == "mu+" ){
		if( particleName == "proton" ){
			fEventAction->AddChE(StDep,PosPX,PosPY,PosPZ);
		}
	}
	//if( (particleName=="e+"&&preProcessName=="UserLimit") || (preProcessName=="annihil") || (preProcessName=="Transportation") ){
	if(EveID<100){
	*fOut << std::setw(4)  << EveID              << "  "
	<< std::setw(3)  << ParID                   << "  "
	<< std::setw(3)  << TraID                    << "  "
	<< std::setw(12) << particleName                              << "  "
	//<< std::setw(10) << PDGNumber                                 << "  "
	//<< std::setw(12) << NowPV  << "  " // materialName, should be pre
	<< std::setw(4)  << CopyN << "  "
	//	  << std::setw(11) << aTrack -> GetVertexPosition()[0]          << "  "
	//	  << std::setw(11) << aTrack -> GetVertexPosition()[1]          << "  "
	//	  << std::setw(11) << aTrack -> GetVertexPosition()[2]          << "  "
	<< std::setw(8) << PrePX         << "  "
	<< std::setw(8) << PrePY         << "  "
	<< std::setw(8) << PrePZ         << "  "
	<< std::setw(8) << PosPX         << "  "
	<< std::setw(8) << PosPY         << "  "
	<< std::setw(8) << PosPZ         << "  "
	<< std::setw(11) << OriEn        << "  " // original (1st) energy
	<< std::setw(11) << CurEn              << "  " // current energy
	//	  << std::setw(11) << aTrack -> GetTotalEnergy()                << "  " // current energy including mass
	<< std::setw(11) << StDep         << "  " // energy deposit in step
	//	  << std::setw(11) << postStepPoint -> GetProperTime() / second << "  " // time in its rest frame since the current track began
	<< std::setw(11) << postStepPoint -> GetGlobalTime() / second << "  " // time since the current event began
	<< std::setw(14) << preProcessName                            << "  "
	<< std::setw(16) << postProcessName                           << "  "
	<< std::setw(16) << originedProcessName                       << G4endl;
	}
}
