using namespace std;

void root_tree_captime_fit(TString root_file)
{
	// set canvas style
	//
	//  gStyle -> SetOptStat(0);   // statistical information (0 = no info, 1 = show info)
	gStyle -> SetOptStat(1);
	//  gStyle -> SetOptFit(1111); // show output result including fit probability (1111)
	gStyle -> SetLabelSize(0.05, "XYZ");
	gStyle -> SetTitleSize(0.06, "XYZ");
	gStyle -> SetTitleOffset(1.0, "X");
	gStyle -> SetTitleOffset(1.1, "Y");
	gStyle -> SetPadLeftMargin(0.14);
	gStyle -> SetPadBottomMargin(0.14);
	gStyle ->SetStripDecimals(false);
	TCanvas *c1 = new TCanvas("c1","canvas",1300,750);
	c1 -> SetFillStyle(4001);
	gPad->SetLogy(1);
	TFile *tf = new TFile(root_file);
	TTree *tr = (TTree*)tf->Get("Tree");

	double CTime;
	tr->SetBranchAddress("CTime",&CTime);
	const Int_t N = tr->GetEntries();
	double captime=0;

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
	// draw histogram
	//
	h1 -> SetLineColor(4);
	h1 -> SetLineWidth(2);
	h1 -> Draw();

	// fit
	//
	//const Double_t FIT_XMIN = XMIN;
	//const Double_t FIT_XMAX = XMAX;
	//const Double_t FIT_XMIN = 1.0e-5;
	//const Double_t FIT_XMAX = 3.0e-5;
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

	// legend
	//
	const Double_t XMAX_RATE = 0.89;
	const Double_t XMIN_RATE = XMAX_RATE - 0.24;
	const Double_t YMAX_RATE = 0.65;
	const Double_t YMIN_RATE = YMAX_RATE - 0.06 * 2;
	TLegend* leg = new TLegend(XMIN_RATE, YMIN_RATE, XMAX_RATE, YMAX_RATE);
	leg -> AddEntry(h1, "Simulation", "L");
	leg -> AddEntry(f1, "Fit",        "L");
	leg -> SetBorderSize(0);
	leg -> SetTextFont(42);
	leg -> SetTextSize(0.05);
	leg -> SetLineColor(0);
	leg -> SetFillStyle(0);
	leg -> Draw();

	gPad -> RedrawAxis(); // draw axis again

	c1 -> Print("CTime_fit.pdf");

	return 0;
}
