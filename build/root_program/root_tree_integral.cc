//draw figure
//root -l 'root_tree_integral.cc("root_file.root")'
//2019/11/25

//Tree -> Print()
//SEne
//SposX SposY SposZ
//CapID
//CposX CposY CposZ
//CTime
//Eabs Elos

using namespace std;

void root_tree_integral(TString root_file){
	TCanvas *c1 = new TCanvas("c1","canvas",1400,850);
	//gPad->SetLogy(1);
	TFile *tf = new TFile(root_file);
	TTree *tr = (TTree*)tf->Get("Tree");

	double Eabs;
	tr->SetBranchAddress("Eabs",&Eabs);
	const Int_t N = tr->GetEntries();

	const Double_t XMIN   = 0;
	const Double_t XMAX   = 10;
	const Double_t XWIDTH = 0.1;

	Int_t bin = (Int_t)((XMAX - XMIN) / XWIDTH + 0.5);
	TH1D *h1 = new TH1D("h1", "", bin, XMIN, XMAX);

	for (Int_t ientry = 0; ientry < N; ientry++) {
		tr->GetEntry(ientry);
		h1->Fill(Eabs);
	}
	h1->Draw();
	TGraph* g1 = new TGraph();
	for(int i=0;i<100;i++){
		g1 -> SetPoint(i, i*0.1, h1->Integral(h1->FindBin(i*0.1), 100) );
	}
	g1 -> SetLineColor(1);
	g1 -> SetLineWidth(1);
	g1 -> SetMarkerColor(1);
	g1 -> SetMarkerStyle(20);
	g1 -> SetMarkerSize(0.8);
	//g1 -> GetXaxis() -> SetLimits(XMIN, XMAX);
	//g1 -> GetYaxis() -> SetRangeUser(YMIN, YMAX);
	g1 -> Draw("ALP");
	c1->Print("integral.pdf");
}
