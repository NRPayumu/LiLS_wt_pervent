//draw figure
//root -l 'root_tree_integral.cc("root_file.root")'
//2020/02/25

//Tree -> Print()
//SEne
//SposX SposY SposZ
//CapID
//CposX CposY CposZ
//CTime
//Eabs Elos

using namespace std;

string den[10] = {"2019121003_0.1_854.root","2019120922_0.2_855.root","2019120917_0.3_855.root",\
  			"2019120913_0.4_856.root","2019112618_neutron.root","2020012417_0.6_858.root",\
			"2020012421_0.7_858.root","2020012720_0.8_859.root","2020012813_0.9_860.root","2019121012_1.0_861.root",};

void captime_integral(){
	//string fin_root ="2020012213.root";
	TCanvas *c1 = new TCanvas("c1","canvas",1300,800);
	gStyle->SetOptStat(kFALSE);
	gStyle->SetStripDecimals(false);

	double CTime;
	double captime=0;
	double Eabs;
	double Edeposit=0;
	const double g1_top = 70000;
	const double g2_top = 60;
	const double dead_t = 1.0; //micro second

	for(int i = 10;i>=10;i--){
		string ifn = Form("root/%s",den[i-1].c_str());
		//gPad->SetLogy(1);
		TFile *tf = new TFile(ifn.c_str());
		TTree *tr = (TTree*)tf->Get("Tree");
		tr->SetBranchAddress("CTime",&CTime);
		tr->SetBranchAddress("Eabs" ,&Eabs);

		const Int_t N = tr->GetEntries();

		const Double_t XMIN   = 1.0e-11 * 1.0e6;
		const Double_t XMAX   = 1.0e-4 * 1.0e6;
		const Double_t XWIDTH = 1.0e-7 * 1.0e6;
		Int_t bin = (Int_t)((XMAX - XMIN) / XWIDTH + 0.5);
		TH1D *h1 = new TH1D("h1", "", bin, XMIN, XMAX);
		TH1D *h2 = new TH1D("h2", "", bin, XMIN, XMAX);

		for (Int_t ientry = 0; ientry < N; ientry++) {
			tr->GetEntry(ientry);
			captime=CTime;
			captime *= 1.0e6;
			h1 -> Fill(captime);
			if(Eabs>=3){
				//captime=CTime;
				//captime *= 1.0e6;
				h2 -> Fill(captime);
			}
		}
		h1->SetLineColor(11-i);
		if(i == 10)h1->Draw();
		if(i != 10)h1->Draw("same");
		h2->Draw("same");
		//h1->Reset("ICESM");

		TGraph* g1 = new TGraph();
		TGraph* g2 = new TGraph();
		for(int i=0;i<1000-h1->FindBin(dead_t);i++){
			//g1 -> SetPoint(i, i, h1->Integral(h1->FindBin(i*0.1), 100) );
			//g1 -> SetPoint(i, i, h1->Integral(h1->FindBin(1.0e-5 +i*0.1), 1000)/1e6 );
			g1 -> SetPoint(i, dead_t+i*0.1, h1->Integral(h1->FindBin(dead_t), h1->FindBin(dead_t+i*0.1))/1e7*(g1_top/g2_top)*100 );
			g2 -> SetPoint(i, dead_t+i*0.1, h2->Integral(h2->FindBin(dead_t), h2->FindBin(dead_t+i*0.1))/1e7*(g1_top/g2_top)*100 );
			//g1 -> SetPoint(i, i, h1->Integral(i, 1000) );
		}
		g1 -> SetLineColor(11-i);
		g1 -> SetLineWidth(1);
		g1 -> SetMarkerColor(11-i);
		g1 -> SetMarkerStyle(20);
		g1 -> SetMarkerSize(0.8);
		//g1 -> GetXaxis() -> SetLimits(XMIN, XMAX);
		//g1 -> GetYaxis() -> SetRangeUser(YMIN, YMAX);
		//g1 -> Draw("ALP");
		g1 -> Draw("same");
		g2 -> Draw("same");
	}
	TGaxis *axis = new TGaxis(100,0,100,g1_top,0,g2_top,510,"+L");
	//TGaxis *axis = new TGaxis(100,0,100,16000,0,5,510,"+L");
	axis -> SetLabelSize(0.035);
	axis -> SetLabelFont(42);
	axis -> Draw();
	c1->Print("integral_captime.pdf");
}

void root_tree_captime_den_cut(){
	//captime();
	captime_integral();
}
