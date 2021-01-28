//draw figure on devided canvas
//root -l 'root_tree_divcanvas_histgram.cc("root_file.root")'
//2019/11/18

//Tree -> Print()
//SEne
//SposX SposY SposZ
//CapID
//CposX CposY CposZ
//Eabs Elos

using namespace std;

void root_tree_divcanvas_neutron(TString root_file){
	//TCanvas *c1 = new TCanvas("c1","canvas",600,400);
	TCanvas *c1 = new TCanvas("c1","canvas",1400,850);
	c1->Divide(2,2);
	//c1->Divide(3,2);

	TFile *tf = new TFile(root_file);
	TTree *tr = (TTree*)tf->Get("Tree");

	c1->cd(1);
	tr->Draw("SEne>>h1(200,0,0.02)");

	c1->cd(2);
	//gPad->SetLogy(1);
	tr->Draw("Eabs>>h2(100,0,10)");
	c1->cd(3);
	gPad->SetLogy(1);
	tr->Draw("Elos>>h3(200,0,10)");
	//c1->cd(4);
	//tr->Draw("SEne:Elos","","");
	//tr->Draw("SEne+0.511*2-Eabs:Elos","","");
	//tr->Draw("SEne:Elos");
	//c1->cd(5);
	//tr->Draw("SEne:Eabs","","");
	//tr->Draw("SEne:Eabs","","surf1");
	//c1->cd(6);
	//tr->Draw("Elos/SEne:SEne","","");
	c1->cd();
	c1->Print("div_c1.pdf");
}
