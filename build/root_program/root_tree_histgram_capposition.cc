//root -l 'root_tree_histgram_capposotion.cc("root_file.root")'
//2019/11/22

//Tree -> Print()
//SEne
//SposX SposY SposZ
//CapID
//CposX CposY CposZ
//CTime
//Eabs Elos

using namespace std;

void root_tree_histgram_capposition(TString root_file){
	//TCanvas *c1 = new TCanvas("c1","canvas",600,400);
	TCanvas *c1 = new TCanvas("c1","canvas",1500,900);

	TFile *tf = new TFile(root_file);
	TTree *tr = (TTree*)tf->Get("Tree");

	double SposX, SposY, SposZ;
	double CposX, CposY, CposZ;
	tr->SetBranchAddress("SposX",&SposX);
	tr->SetBranchAddress("SposY",&SposY);
	tr->SetBranchAddress("SposZ",&SposX);
	tr->SetBranchAddress("CposX",&CposX);
	tr->SetBranchAddress("CposY",&CposY);
	tr->SetBranchAddress("CposZ",&CposZ);
	const Int_t N = tr->GetEntries();
	double Range=350;

	const Double_t XMIN   = 0;
	const Double_t XMAX   = 400;
	const Double_t XWIDTH = 1.0;
	Int_t bin = (Int_t)((XMAX - XMIN) / XWIDTH + 0.5);
	TH1D *h1 = new TH1D("h1", "", bin, XMIN, XMAX);

	for (Int_t ientry = 0; ientry < N; ientry++) {
		Range=350;
		tr->GetEntry(ientry);
		if(CposX!=0){
			Range=sqrt( (SposX-CposX)*(SposX-CposX)+(SposY-CposY)*(SposY-CposY)+(SposZ-CposZ)*(SposZ-CposZ) );
		}
		h1 -> Fill(Range);
	}

	//tr->Draw("SEne:Range");
	h1 -> SetLineColor(4); // 2: red, 3: green, 4: blue
	h1 -> SetLineWidth(2);
	h1 -> Draw();
	c1->Print("capposition.pdf");
}
