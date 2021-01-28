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

void root_tree_captime(TString root_file){
	//string fin_root ="2019112618_neutron.root";
	//string fin_root ="2019120913_0.4_856.root";
	//string fin_root ="2019120917_0.3_855.root";
	//string fin_root ="2019120922_0.2_855.root";
	//string fin_root ="2019121003_0.1_854.root";
	//string fin_root ="2019121012_1.0_861.root";
	//string fin_root ="2020012213.root";

	TCanvas *c1 = new TCanvas("c1","canvas",1300,800);
	gStyle->SetOptStat(kFALSE);
	gStyle->SetStripDecimals(false);
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

	const Double_t FIT_XMIN = 10.;
	const Double_t FIT_XMAX = 30.;
	//TF1 *f1 = new TF1("f1", "gaus(0) + [3] * exp(-x/[4])", FIT_XMIN, FIT_XMAX);
	TF1 *f1 = new TF1("f1", "[0] * exp(-x/[1])", FIT_XMIN, FIT_XMAX);
	f1 -> SetParNames("A", "#lambda");
	f1 -> SetParameter(0, 400000);
	//f1 -> SetParameter(1, 3.0e-6);
	f1 -> SetParameter(1, 3.0);
	f1 -> SetLineColor(2);
	h1 -> Fit("f1", "R", "same");
	f1 -> Draw( "same" );

	Double_t A        = f1 -> GetParameter(0);
	Double_t AErr     = f1 -> GetParError(0);
	Double_t lambda   = f1 -> GetParameter(1);
	Double_t lamErr   = f1 -> GetParError(1);

	//cout << "A     =" << A      << endl;
	//cout << "AErr  =" << AErr   << endl;
	//cout << "lambda=" << lambda << endl;
	//cout << "almErr=" << lamErr << endl;

	//cout << h1->FindBin(5.) << endl;

	const double g1_top = 70000;
	const double g2_top = 60;
	const double dead_t = 1.0;

	TGraph* g1 = new TGraph();
	for(int i=0;i<1000-h1->FindBin(dead_t);i++){
		//g1 -> SetPoint(i, i, h1->Integral(h1->FindBin(i*0.1), 100) );
		//g1 -> SetPoint(i, i, h1->Integral(h1->FindBin(1.0e-5 +i*0.1), 1000)/1e6 );
		g1 -> SetPoint(i, dead_t+i*0.1, h1->Integral(h1->FindBin(dead_t), h1->FindBin(dead_t+i*0.1))/1e7*(g1_top/g2_top)*100 );
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

	TGaxis *axis = new TGaxis(100,0,100,g1_top,0,g2_top,510,"+L");
	//TGaxis *axis = new TGaxis(100,0,100,16000,0,5,510,"+L");
	axis -> SetLabelSize(0.035);
	axis -> SetLabelFont(42);
	axis -> Draw();
	c1->Print("integral_captime.pdf");
}
