//draw figure on devided canvas
//root -l 'root_tree_divcanvas_histgram.cc("root_file.root")'
//2019/11/22

//Tree -> Print()
//SEne
//SposX SposY SposZ
//CapID
//CposX CposY CposZ
//CTime
//Eabs Elos

using namespace std;

void root_tree_divcanvas_histgram_captime(TString root_file){
	TCanvas *c1 = new TCanvas("c1","canvas",600,400);
	//TCanvas *c1 = new TCanvas("c1","canvas",1500,900);

	TFile *tf = new TFile(root_file);
	TTree *tr = (TTree*)tf->Get("Tree");
	gPad->SetLogy(1);
	tr->Draw("CTime>>h4(10000,0,0.0001)");
	c1->Print("captime.pdf");
}
