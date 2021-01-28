Int_t root_3D()
{ 
  // make canvas
  //
  TCanvas *c1 = new TCanvas("c1", "", 800, 600);

  // make ntuple
  //  
  TNtuple *ntuple = new TNtuple("ntuple", "", "x:y:z");

  ifstream fin("hoge");
  Double_t x, y, z;
  while (!fin.eof()) {
    fin >> x >> y >> z;
    ntuple -> Fill(x,y,z);
  }
  fin.close();

  ntuple -> SetMarkerColor(5);
  ntuple -> SetMarkerSize(1.0);
  ntuple -> SetMarkerStyle(20);
  ntuple -> Draw("z:y:x");  
  ntuple -> GetHistogram() -> GetXaxis() -> SetTitle("X");
  ntuple -> GetHistogram() -> GetXaxis() -> SetTitleOffset(1.2);
  ntuple -> GetHistogram() -> GetYaxis() -> SetTitle("Y");
  ntuple -> GetHistogram() -> GetYaxis() -> SetTitleOffset(1.7);
  ntuple -> GetHistogram() -> GetZaxis() -> SetTitle("Z"); 
  ntuple -> GetHistogram() -> GetZaxis() -> SetTitleOffset(1.2);
  ntuple -> GetHistogram() -> GetZaxis() -> SetTitleOffset(1.2);

  // make output
  TFile *tfout = new TFile("hoge.root", "RECREATE");
  ntuple -> Write();

  return 0;
}
