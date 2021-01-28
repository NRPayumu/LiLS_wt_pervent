// source: $G4INSTALL/examples/novice/N03/exampleN03.cc
// source: $G4INSTALL/examples/examples/extended/analysis/AnaEx02/AnaEx02.cc
// 2020/06/16
// recommend to use atom edditor. not exist coding.
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

#include "Shielding.hh" // PhysicsList

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//extern G4String OutRoot;

int main(int argc,char** argv)
{
	//---------------------------------------------------------------------------------//
	G4String datFileName = "data_step.dat";
	G4String PriFile     = "E_nu.dat";
	G4String Rootfile    = "ERoot";
	if (argc == 1 || 5 < argc) {
		G4cerr << "-----------------------------------------------------------" << G4endl
		<< " Usage: " << argv[0] << " InputMacro OutputDatFile PrimalEnergy root_file" << G4endl
		<< "-----------------------------------------------------------"   << G4endl;
		exit(8);
	}

	if (argc == 3) {
		datFileName = argv[2];
	}
	if (argc == 4) {
		datFileName = argv[2];
		PriFile = argv[3];
	}
	if (argc == 5) {
		datFileName = argv[2];
		PriFile     = argv[3];
		Rootfile    = argv[4];
	}
	//---------------------------------------------------------------------------------//

	// change random seed
	long seed = time(NULL);
	G4Random::setTheSeed(seed);

	// Construct the default run manager
	//
	G4RunManager* runManager = new G4RunManager;

	// Set mandatory initialization classes
	//
	DetectorConstruction* detector = new DetectorConstruction;
	runManager -> SetUserInitialization(detector);
	//
	// ref. Physics lists Use cases --- http://geant4.cern.ch/support/proc_mod_catalog/physics_lists/useCases.shtml
	G4VModularPhysicsList* physics = new Shielding; // Shielding applications, underground physics
	runManager -> SetUserInitialization(physics);

	// Set user action classes
	//
	//PrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction();
	PrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction(PriFile);

	runManager -> SetUserAction(gen_action);
	//
	//RunAction* run_action = new RunAction();
	RunAction* run_action = new RunAction(Rootfile);
	runManager -> SetUserAction(run_action);
	//
	EventAction* event_action = new EventAction(run_action, gen_action);
	runManager -> SetUserAction(event_action);
	//
	//  G4UserSteppingAction* stepping_action = new MySteppingAction(detector, event_action);
	G4UserSteppingAction* stepping_action = new SteppingAction(detector, event_action, datFileName);
	runManager -> SetUserAction(stepping_action);

	// Initialize G4 kernel
	//
	runManager -> Initialize();

	#ifdef G4VIS_USE
	// Initialize visualization
	//
	G4VisManager* visManager = new G4VisExecutive;
	visManager -> Initialize();
	#endif

	// Get the pointer to the User Interface manager
	//
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	if (argc != 1)   // batch mode
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager -> ApplyCommand(command+fileName);
	}
	else
	{  // interactive mode : define UI session
		#ifdef G4UI_USE
		G4UIExecutive* ui = new G4UIExecutive(argc, argv);
		#ifdef G4VIS_USE
		UImanager -> ApplyCommand("/control/execute vis.mac");
		#endif
		if (ui -> IsGUI())
		UImanager -> ApplyCommand("/control/execute gui.mac");
		ui -> SessionStart();
		delete ui;
		#endif
	}

	// Job termination
	// Free the store: user actions, physics_list and detector_description are
	//                 owned and deleted by the run manager, so they should not
	//                 be deleted in the main() program !
	#ifdef G4VIS_USE
	delete visManager;
	#endif
	delete runManager;

	return 0;
}
