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

void root_tree_histgram(TString root_file){
	TCanvas *c1 = new TCanvas("c1","canvas",600,400);

	TFile *tf = new TFile(root_file);
	TTree *tr = (TTree*)tf->Get("Tree");
	tr->Draw("SEne>>h1(100,0,10)");
	tr->Draw("Eabs>>h2(100,0,10)","","same");
	//tr->Scan("SEne");
	c1->Print("draw.pdf");
}

int main(){
	root_tree_histgram("test.root");
	return 0;
}
