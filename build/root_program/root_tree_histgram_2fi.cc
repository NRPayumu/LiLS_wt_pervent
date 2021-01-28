//tree to histgram
//root -l 'root_tree_histgram.cc("root_file.root")'

//Tree -> Print()
//SEne
//SposX SposY SposZ
//CapID
//CposX CposY CposZ
//Eabs Elos

#include <string>
#include "TFile.h"
#include "TTree.h"

using namespace std;

void root_tree_histgram_2fi(TString root_file, TString root_file2){
	TCanvas *c1 = new TCanvas("c1","canvas",600,400);

	TFile *tf = new TFile(root_file);
	TTree *tr = (TTree*)tf->Get("Tree");

	TFile *tf2 = new TFile(root_file2);
	TTree *tr2 = (TTree*)tf2->Get("Tree");

	double SEne,Eabs;
	tr->SetBranchAddress("SEne",&SEne);
	tr->SetBranchAddress("Eabs",&Eabs);
	const Int_t N = tr->GetEntries();

	double Eabs2;
	tr2->SetBranchAddress("Eabs",&Eabs2);
	const Int_t N2 = tr2->GetEntries();

	const Double_t XMIN   = 0;
	const Double_t XMAX   = 10;
	const Double_t XWIDTH = 0.1;

	Int_t bin = (Int_t)((XMAX - XMIN) / XWIDTH + 0.5);
	TH1D *h1 = new TH1D("h1", "", bin, XMIN, XMAX);
	TH1D *h2 = new TH1D("h2", "", bin, XMIN, XMAX);
	TH1D *h3 = new TH1D("h3", "", bin, XMIN, XMAX);
	TH1D *h4 = new TH1D("h4", "", bin, XMIN, XMAX);
	//h1->SetFillColor(kRed);
	h3->SetFillColor(kGreen);
	//h2->SetFillColor(kBlue);
	h4->SetFillColor(kBlue);

	/*for (Int_t ientry = 0; ientry < N; ientry++) {
		tr->GetEntry(ientry);
		h1->Fill(Eabs);
		h3->Fill(SEne);
	}

	for (Int_t ientry = 0; ientry < N2; ientry++) {
		tr2->GetEntry(ientry);
		h2->Fill(Eabs2);
	}
	for (Int_t ientry = 0; ientry < N2; ientry++) {
		h4->SetBinContent(ientry,h2->GetBinContent(ientry) /10 );
	}
	h2->Scale(0.1);*/

	for (Int_t ientry = 0; ientry < N; ientry++) {
		tr ->GetEntry(ientry);
		tr2->GetEntry(ientry);
		h1->Fill(SEne+Eabs2);
	}
	h1->Draw();
	/*THStack *hs = new THStack("hs","test stacked histograms");
	//hs->Add(h1);
	//hs->Add(h2);
	hs->Add(h4);
	hs->Add(h3);
	hs->Draw();*/
	c1->Print("stac_hist.pdf");
}

int main(){
	root_tree_histgram_2fi("test.root","test2.root");
	return 0;
}
