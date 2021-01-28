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

void root_tree_integral_captime(TString root_file){
	TCanvas *c1 = new TCanvas("c1","canvas",1400,850);
	gStyle->SetOptStat(kFALSE);
	//gPad->SetLogy(1);
	TFile *tf = new TFile(root_file);
	TTree *tr = (TTree*)tf->Get("Tree");

	double CTime;
	double captime=0;
	tr->SetBranchAddress("CTime",&CTime);
	const Int_t N = tr->GetEntries();

	const Double_t XMIN   = 1.0e-11 * 1.0e6;
	const Double_t XMAX   = 1.0e-4 * 1.0e6;
	const Double_t XWIDTH = 1.0e-7 * 1.0e6;
	Int_t bin = (Int_t)((XMAX - XMIN) / XWIDTH + 0.5);
	TH1D *h1 = new TH1D("h1", "", bin, XMIN, XMAX);

	for (Int_t ientry = 0; ientry < N; ientry++) {
		tr->GetEntry(ientry);
		captime=CTime;
		captime *= 1.0e6;
		h1 -> Fill(captime);
	}

	h1->Draw();

	//cout << h1->FindBin(5.) << endl;
	TGraph* g1 = new TGraph();
	for(int i=0;i<1000-h1->FindBin(5.);i++){
		//g1 -> SetPoint(i, i, h1->Integral(h1->FindBin(i*0.1), 100) );
		//g1 -> SetPoint(i, i, h1->Integral(h1->FindBin(1.0e-5 +i*0.1), 1000)/1e6 );
		g1 -> SetPoint(i, 5+i*0.1, h1->Integral(h1->FindBin(5.), h1->FindBin(5.+i*0.1))/1e6*(16000/4.5) );
		//g1 -> SetPoint(i, i, h1->Integral(i, 1000) );
	}
	g1 -> SetLineColor(1);
	g1 -> SetLineWidth(1);
	g1 -> SetMarkerColor(1);
	g1 -> SetMarkerStyle(20);
	g1 -> SetMarkerSize(0.8);
	//g1 -> GetXaxis() -> SetLimits(XMIN, XMAX);
	//g1 -> GetYaxis() -> SetRangeUser(YMIN, YMAX);
	//g1 -> Draw("ALP");
	g1 -> Draw("same");

	TGaxis *axis = new TGaxis(100,0,100,16000,0,4.5,510,"+L");
	//TGaxis *axis = new TGaxis(100,0,100,16000,0,5,510,"+L");
	//axis -> SetFontSize(4);
	axis -> Draw();
	c1->Print("integral_captime.pdf");
}
