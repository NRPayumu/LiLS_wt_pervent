//draw figure
//root -l 'root_tree_divcanvas_integ.cc("root_file.root")'
//2019/11/19

//Tree -> Print()
//SEne
//SposX SposY SposZ
//CapID
//CposX CposY CposZ
//CTime
//Eabs Elos

using namespace std;

void root_tree_divcanvas_integ(TString root_file){
	TCanvas *c1 = new TCanvas("c1","canvas",1400,850);
	//gPad->SetLogy(1);
	tr->Draw("Eabs>>h1(100,0,10)");

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
	c1->Print("div_c1.pdf");
}
