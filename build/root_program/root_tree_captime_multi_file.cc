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

void captime(){
	//string fin_root ="2020012213.root";
	TCanvas *c1 = new TCanvas("c1","canvas",1300,800);
	gStyle->SetOptStat(kFALSE);
	gStyle->SetStripDecimals(false);

	double CTime;
	double captime=0;

	for(int i = 10;i>=1;i--){
		string ifn = Form("root/%s",den[i-1].c_str());
		gPad->SetLogy(1);
		TFile *tf = new TFile(ifn.c_str());
		TTree *tr = (TTree*)tf->Get("Tree");
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
		if(i!=10)h1->SetLineColor(11-i);
		if(i==10)h1->SetLineColor(11);
		if(i == 10)h1->Draw();
		if(i != 10)h1->Draw("same");
		//h1->Reset("ICESM");

		//const Double_t YMIN   = 0.0;
		//const Double_t YMAX   = 1.0e6;
		//h1 -> GetXaxis() -> SetLimits(XMIN, XMAX);
		//h1 -> GetYaxis() -> SetRangeUser(YMIN, YMAX);
		/*
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
		*/
	}
	c1->Print("captime.pdf");
}

void captime_integral(){
	//string fin_root ="2020012213.root";
	TCanvas *c1 = new TCanvas("c1","canvas",1300,800);
	gStyle->SetOptStat(kFALSE);
	gStyle->SetStripDecimals(false);

	//gPad->SetLogy(1);

	double CTime;
	double captime=0;
	const double g1_top = 70000;
	const double g2_top = 70;
	const double dead_t = 1.0; //micro second

	for(int i = 10;i>=1;i--){
		int c = 0;
		int c2= 0;
		int c3= 0;
		string ifn = Form("root/%s",den[i-1].c_str());
		TFile *tf = new TFile(ifn.c_str());
		TTree *tr = (TTree*)tf->Get("Tree");
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
		if(i!=1)h1->SetLineColor(11-i);
		if(i==1)h1->SetLineColor(11);
		if(i == 10)h1->Draw();
		if(i != 10)h1->Draw("same");
		//h1->Draw();
		//h1->Reset("ICESM");

		TGraph* g1 = new TGraph();
		//for(int j=0;j<1000-h1->FindBin(dead_t);j++){
		for(int j=0;j<1000-dead_t*10;j++){
			//g1 -> SetPoint(j, j, h1->Integral(h1->FindBin(j*0.1), 100) );
			//g1 -> SetPoint(j, j, h1->Integral(h1->FindBin(1.0e-5 +j*0.1), 1000)/1e6 );
			g1 -> SetPoint(j, dead_t+j*0.1, h1->Integral(h1->FindBin(dead_t), h1->FindBin(dead_t+j*0.1))/1e7*(g1_top/g2_top)*100 );
			//g1 -> SetPoint(j, dead_t+j*0.1, h1->Integral(h1->FindBin(dead_t), h1->FindBin(dead_t+j*0.1))/1e7*100 );
			//g1 -> SetPoint(j, j, h1->Integral(j, 1000) );

			if( h1->Integral(h1->FindBin(dead_t), h1->FindBin(dead_t+j*0.1)) >= (h1->Integral(h1->FindBin(dead_t), h1->FindBin(dead_t+99.9))*0.95) && c==0 ){
				cout << "95perMax time = " << dead_t+j*0.1 << endl;
				c =1;
			}
			if( h1->Integral(h1->FindBin(dead_t), h1->FindBin(dead_t+j*0.1))/1e7*100 >= 50 && c2 == 0){
				cout << "50perAll time = " << dead_t+j*0.1 << endl;
				c2=1;
			}
			if( c3==0 ){
				cout << "time 30 yield = " << h1->Integral(h1->FindBin(dead_t), h1->FindBin(30))/1e7*100 << endl;
				c3=1;
			}
			//if(j%50==0 && i == 1){
			//	cout << "time = " << dead_t+j*0.1 << " : per = " << h1->Integral(h1->FindBin(dead_t), h1->FindBin(dead_t+j*0.1))/1e7*100 << " : bin" << h1->FindBin(dead_t+j*0.1) << endl;
			//}
		}
		if(i!=1)g1 -> SetLineColor(11-i);
		if(i==1)g1 -> SetLineColor(11);
		g1 -> SetLineWidth(1);
		if(i!=1)g1 -> SetMarkerColor(11-i);
		if(i==1)g1 -> SetMarkerColor(11);
		g1 -> SetMarkerStyle(20);
		g1 -> SetMarkerSize(1.2);
		//g1 -> GetXaxis() -> SetLimits(XMIN, XMAX);
		//g1 -> GetYaxis() -> SetRangeUser(YMIN, YMAX);
		//g1 -> Draw("ALP");
		g1 -> Draw("same");
		//if(i == 10)g1->Draw("ALP");
		//if(i != 10)g1->Draw("same");
	}
	TGaxis *axis = new TGaxis(100,0,100,g1_top,0,g2_top,510,"+L");
	//TGaxis *axis = new TGaxis(100,0,100,16000,0,5,510,"+L");
	axis -> SetLabelSize(0.035);
	axis -> SetLabelFont(42);
	axis -> Draw();
	c1->Print("integral_captime.pdf");
}

void root_tree_captime_multi_file(){
	//captime();
	captime_integral();
}
