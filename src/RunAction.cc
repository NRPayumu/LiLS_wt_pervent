// 2020/07/21
//
#include "G4Run.hh"
#include "G4RunManager.hh"

#include "RunAction.hh"
#include "EventAction.hh"

#include <fstream>
#include <iostream>
#include <sstream>

#include "g4root.hh"

#include "G4SystemOfUnits.hh"
#include <time.h>
#include "variable.h"

#ifndef __CINT__
#include "TFile.h"
#include "TTree.h"
#endif

using namespace std;

G4String OutRoot="DefRoot";

RunAction::RunAction()
{
  auto analysisManager = G4AnalysisManager::Instance();
  //G4String fileName = "Aroot";
  //analysisManager->OpenFile(fileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  analysisManager->CreateNtuple("Tree", "Tree");
  analysisManager->CreateNtupleDColumn("SEne");
  /*analysisManager->CreateNtupleDColumn("SposX");
  analysisManager->CreateNtupleDColumn("SposY");
  analysisManager->CreateNtupleDColumn("SposZ");
  analysisManager->CreateNtupleDColumn("CapID");
  analysisManager->CreateNtupleDColumn("CposX");
  analysisManager->CreateNtupleDColumn("CposY");
  analysisManager->CreateNtupleDColumn("CposZ");
  analysisManager->CreateNtupleDColumn("CTime");*/
  analysisManager->CreateNtupleDColumn("Eabs");
  analysisManager->CreateNtupleDColumn("Elos");
  analysisManager->CreateNtupleDColumn("LenG");
  analysisManager->CreateNtupleDColumn("GrvX");
  analysisManager->CreateNtupleDColumn("GrvY");
  analysisManager->CreateNtupleDColumn("GrvZ");
  analysisManager->CreateNtupleDColumn("CEabs");
  analysisManager->CreateNtupleDColumn("ChaGX");
  analysisManager->CreateNtupleDColumn("ChaGY");
  analysisManager->CreateNtupleDColumn("ChaGZ");
  analysisManager->FinishNtuple();
  /*
  analysisManager->CreateNtupleSColumn("Detector_Name");
  analysisManager->CreateNtupleSColumn("Detector_Name");
  analysisManager->CreateNtupleDColumn("year");
  analysisManager->CreateNtupleDColumn("date");
  analysisManager->CreateNtupleDColumn("World_Size");
  analysisManager->CreateNtupleDColumn("Detector_Size");
  analysisManager->CreateNtupleDColumn("Gd_fractionmass");
  analysisManager->CreateNtupleSColumn("Particle_Name");
  analysisManager->FinishNtuple(1);
  //analysisManager->FillNtupleSColumn(NtupleID,ColumnID+0,Form("%s",Detector_symbolic_Name) );
  analysisManager->AddNtupleRow();
  analysisManager->Write();*/
}
RunAction::RunAction(G4String RootFileName)
{
  auto analysisManager = G4AnalysisManager::Instance();
  //analysisManager->OpenFile(fileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  analysisManager->CreateNtuple("Tree", "Tree");
  analysisManager->CreateNtupleDColumn("SEne");
  analysisManager->CreateNtupleDColumn("SposX");
  analysisManager->CreateNtupleDColumn("SposY");
  analysisManager->CreateNtupleDColumn("SposZ");
  analysisManager->CreateNtupleDColumn("CapID");
  analysisManager->CreateNtupleDColumn("CposX");
  analysisManager->CreateNtupleDColumn("CposY");
  analysisManager->CreateNtupleDColumn("CposZ");
  analysisManager->CreateNtupleDColumn("CTime");
  analysisManager->CreateNtupleDColumn("Eabs");
  analysisManager->CreateNtupleDColumn("Elos");
  analysisManager->CreateNtupleDColumn("LenG");
  analysisManager->CreateNtupleDColumn("GrvX");
  analysisManager->CreateNtupleDColumn("GrvY");
  analysisManager->CreateNtupleDColumn("GrvZ");
  analysisManager->CreateNtupleDColumn("CEabs");
  analysisManager->CreateNtupleDColumn("ChaGX");
  analysisManager->CreateNtupleDColumn("ChaGY");
  analysisManager->CreateNtupleDColumn("ChaGZ");
  analysisManager->FinishNtuple();

  /*
  G4int year = tm.tm_year + 1900;
  G4int date = (tm.tm_mon+1)*100 + (tm.tm_mday)*1;
  //G4int event= aRun -> GetNumberOfEvent();
  G4String DetName = Detector_symbolic_Name;
  G4String ParName = Particle_Name;
  G4double WorSize = worldBoxSizeXY;
  G4double DetSize = GdLSSizeX;
  G4double Gdfract = Gd_fractionmass;

  TTree *Run = new TTree("Info", "RunInformation");
  analysisManager->CreateNtuple("Info", "RunInfo");
  Run -> Branch("DetectorName", &DetName, "DetName/S");
  Run -> Branch("year", &year, "year/I");
  Run -> Branch("date", &date, "date/I");
  //Run -> Branch("event", &Event, "Event/I");
  Run -> Branch("WorldSize", &WorSize, "WorSize/D");
  Run -> Branch("DetectorSize", &DetSize, "DetSize/D");
  Run -> Branch("Gd_w%", &Gdfract, "Gdfract/D");
  Run -> Branch("ParticleName", &ParName, "ParName/S");
  //analysisManager->FillNtupleSColumn(NtupleID,ColumnID+0,Form("%s",Detector_symbolic_Name) );
  Run -> Fill();
  Run -> Write();*/

  OutRoot = RootFileName;
}

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun -> GetRunID() << " start." << G4endl;
  auto analysisManager = G4AnalysisManager::Instance();

  struct tm tm;
  time_t t = time(NULL);
  localtime_r(&t, &tm);
  if(OutRoot=="ERoot"){
    OutRoot =  std::to_string( (tm.tm_year + 1900)*1000000 +
    (tm.tm_mon+1)*10000 + (tm.tm_mday)*100 +(tm.tm_hour) );
  }
  //analysisManager->OpenFile(fileName);
  analysisManager->OpenFile(OutRoot);
}

/*void RunAction::BeginOfRunAction(const G4Run* aRun, G4String RootFileName)
{
G4cout << "### Run " << aRun -> GetRunID() << " start." << G4endl;
auto analysisManager = G4AnalysisManager::Instance();

G4String fileName = "Aroot";

struct tm tm;
time_t t = time(NULL);
localtime_r(&t, &tm);
//fileName = std::to_string( RootFileName );
fileName = RootFileName;
fileName = "Aroot";
analysisManager->OpenFile(fileName);

//cout << endl << endl << OutRoot << endl <<endl;
//analysisManager->OpenFile(OutRoot);
}*/

void RunAction::EndOfRunAction(const G4Run*)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  /*
  const G4int NtupleID = 1;
  const G4int ColumnID = 0;
  struct tm tm;
  time_t t = time(NULL);
  localtime_r(&t, &tm);
  analysisManager->FillNtupleSColumn(NtupleID,ColumnID+0,"Gd-LS");
  //analysisManager->FillNtupleSColumn(NtupleID,ColumnID+0,Form("%s",Detector_symbolic_Name) );
  analysisManager->FillNtupleDColumn(NtupleID,ColumnID+1,tm.tm_year + 1900);
  analysisManager->FillNtupleDColumn(NtupleID,ColumnID+2,(tm.tm_mon+1)*100 + (tm.tm_mday)*1);
  analysisManager->FillNtupleDColumn(NtupleID,ColumnID+3,worldBoxSizeXY);
  analysisManager->FillNtupleDColumn(NtupleID,ColumnID+4,GdLSSizeX);
  analysisManager->FillNtupleDColumn(NtupleID,ColumnID+5,Gd_fractionmass);
  analysisManager->FillNtupleSColumn(NtupleID,ColumnID+6,Particle_Name);
  analysisManager->AddNtupleRow(NtupleID);
  analysisManager->Write();*/

  analysisManager->CloseFile();
  //  G4double eventNo = aRun -> GetNumberOfEvent();
}
