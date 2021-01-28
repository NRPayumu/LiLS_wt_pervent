//root -l Gene_hist.cc'("test_hist",100000)' 2>E_nu.dat

#define ReactorX 24.//m
#define ReactorY 0.
#define ReactorZ 0.

#define DetectorX 1.//m
#define DetectorY 0.1//m
#define DetectorZ 0.2//m

#define FRateU235 7.8/12.2//7.8e+19;
#define FRateU238 0.9/12.2//0.9e+19
#define FRatePu239 2.9/12.2//2.9e+19
#define FRatePu241 0.6/12.2//0.6e+19

#define CORMAXRATE 1.2
#define EMID 6.//MeV
#define EMIN 0.
#define EMAX 12.
#define dE 0.001

const double m_e = 0.511;//MeV
const double M_p = 938.27203;//MeV
const double M_n = 939.56536;//MeV

TVector3 numom;

TRandom3 rand0,rand1,rand2,rand3,rand4,rand5;

double fU235[6];
double fU238[3];
double fPu239[6];
double fPu241[6];
double fU235e[6];
double fU238e[3];
double fPu239e[6];
double fPu241e[6];

void init (void)
{
	int isono,fno;

	ifstream file("fissionphuber.txt");


	file>>isono;
	cout<<isono<<endl;
	for(int i=0;i<6;i++)file>>fno>>fU235[i]>>fU235e[i];
	file>>isono;
	cout<<isono<<endl;
	for(int i=0;i<6;i++)file>>fno>>fPu239[i]>>fPu239e[i];
	file>>isono;
	cout<<isono<<endl;
	for(int i=0;i<6;i++)file>>fno>>fPu241[i]>>fPu241e[i];

	file>>isono;
	for(int i=0;i<3;i++)file>>fno>>fU238[i]>>fU238e[i];
}

TVector3 GetVertexPostion (void)
{
	double xv,yv,zv,flag;
	TVector2 tpos;
	TVector3 vpos,vpos1;

	xv=DetectorX*(rand0.Rndm()-0.5);
	yv=DetectorY*(rand1.Rndm()-0.5);
	zv=DetectorZ*(rand2.Rndm()-0.5);
	vpos.SetXYZ(xv,yv,zv);

	return vpos;

}

double CalNeutrinoSpectrum(double E_nu, double cos_theta){
	const double dM = M_n - M_p;//MeV
	const double M = (M_p+M_n)/2;//MeV
	const double f = 1.0;
	const double g = 1.267;
	const double sigma0 = 0.952e-42/(f*f+3*g*g);
	const double f2 = 3.706;//mu_p - mu_n
	const double y2 = (dM*dM - m_e*m_e)/2.;

	double rate235=0.;
	double rate238=0.;
	double rate239=0.;
	double rate241=0.;

	//if(E_nu>1.8&&E_nu<10){
	for(int nd=0;nd<6;nd++){
		rate235+=fU235[nd]*pow(E_nu,nd);
		rate239+=fPu239[nd]*pow(E_nu,nd);
		rate241+=fPu241[nd]*pow(E_nu,nd);
	}
	for(int nd=0;nd<3;nd++)rate238+=fU238[nd]*pow(E_nu,nd);
	//}

	double totalRate=exp(rate235)*FRateU235+exp(rate238)*FRateU238+exp(rate239)*FRatePu239+exp(rate241)*FRatePu241;

	const double E_e0 = E_nu - dM;
	const double p_e0 = sqrt(E_e0*E_e0 - m_e*m_e);
	const double v_e0 = p_e0/E_e0;
	const double E_e1 = E_e0*(1 - E_nu/M*(1-v_e0*cos_theta)) - y2/M;
	const double p_e1 = sqrt(E_e1*E_e1 - m_e*m_e);
	const double v_e1 = p_e1/E_e1;

	if(v_e0 <= 0) return 0;

	const double Gamma = 2*(f+f2)*((2*E_e0+dM)*(1-v_e0*cos_theta) - m_e*m_e/E_e0)
	+ (f*f+g*g)*(dM*(1+v_e0*cos_theta) + m_e*m_e/E_e0)
	+ (f*f+3*g*g)*((E_e0+dM)*(1-1./v_e0*cos_theta) + dM)
	+ (f*f-g*g)*((E_e0+dM)*(1-1./v_e0*cos_theta) + dM)*v_e0*cos_theta;


	double DCrossSection=sigma0/2*((f*f + 3*g*g) + (f*f - g*g)*v_e1*cos_theta)*E_e1*p_e1
	- sigma0/2*Gamma/M*E_e0*p_e0;

	if(v_e0 <= 0) DCrossSection=0;

	return totalRate*DCrossSection;
}


double GetNeutrinoMomentum(TVector3 nudirect, double *posimom,double *neutronmom)
{

	const double pi = 4* atan(1);
	const double dM = M_n - M_p;//MeV
	const double M = (M_p+M_n)/2;//MeV
	const double y2 = (dM*dM - m_e*m_e)/2;

	TVector3 emom,nmom,vv,fPositronMomemtum,fNeutronMomemtum;

	double E_nu, phi, theta, cos_theta;
	double nu,ans,maxans,rate;

	do{
		maxans=CalNeutrinoSpectrum(3.5,-1);

		E_nu=rand3.Rndm()*(EMAX-1.806)+1.806;
		cos_theta=2.*rand4.Rndm()-1.;
		ans=CalNeutrinoSpectrum(E_nu,cos_theta);
		rate=maxans*CORMAXRATE*rand5.Rndm();
	}while(rate>ans);

	theta = acos(cos_theta);
	phi=2.*TMath::Pi()*rand0.Rndm();

	//numom=E_nu*nudirect;

	vv = TVector3(0.,1.,1.);

	double y,tmpy,Ee,tmpEe,En,cos_alpha,alpha;
	int maxeve=(int)((EMAX-EMIN)/dE);

	tmpy=1.0e+08;
	tmpEe=-10000.;

	for(int i=0;i<maxeve;i++){
		Ee=i*dE;
		y=E_nu-dM-(E_nu*E_nu-2.*E_nu*Ee*cos_theta+Ee*Ee)/(2.*M_n)
		-sqrt(m_e*m_e+Ee*Ee);

		if(tmpy>fabs(y)){
			tmpy=fabs(y);
			tmpEe=Ee;
		}
	}

	y=tmpy;
	Ee=tmpEe;

	En=sqrt(E_nu*E_nu-2.*E_nu*Ee*cos_theta+Ee*Ee);
	//cout << En << endl;
	cos_alpha=(E_nu-Ee*cos_theta)/En;
	alpha=acos(cos_alpha);

	emom.SetXYZ(Ee*sin(theta)*cos(phi),Ee*sin(theta)*sin(phi),Ee*cos(theta));
	nmom.SetXYZ(En*sin(alpha)*cos(phi+TMath::Pi()),En*sin(alpha)*sin(phi+TMath::Pi()),En*cos(alpha));

	emom.RotateY(acos(nudirect.Z()/nudirect.Mag()));
	emom.RotateZ(acos(nudirect.X()/nudirect.Perp()));
	fPositronMomemtum.SetXYZ(emom.X(),emom.Y(),emom.Z());

	nmom.RotateY(acos(nudirect.Z()/nudirect.Mag()));
	nmom.RotateZ(acos(nudirect.X()/nudirect.Perp()));
	fNeutronMomemtum.SetXYZ(nmom.X(),nmom.Y(),nmom.Z());

	posimom[0]=fPositronMomemtum.X();
	posimom[1]=fPositronMomemtum.Y();
	posimom[2]=fPositronMomemtum.Z();

	neutronmom[0]=fNeutronMomemtum.X();
	neutronmom[1]=fNeutronMomemtum.Y();
	neutronmom[2]=fNeutronMomemtum.Z();

	return E_nu;
}

void Gene_hist(string st, int NEVENT)
{
	gStyle -> SetOptStat(0);
	gStyle -> SetStatX(0.9);
	gStyle -> SetStatY(0.9);
	gStyle -> SetLabelSize(0.05, "XY");
	gStyle -> SetTitleSize(0.06, "XY");
	gStyle -> SetTitleOffset(1.0, "X");
	gStyle -> SetTitleOffset(1.1, "Y");
	gStyle -> SetPadLeftMargin(0.14);
	gStyle -> SetPadBottomMargin(0.14);
	TCanvas *c1 = new TCanvas("c1", "", 800, 600); // x-size, y-size = 800, 600
	c1 -> SetFillStyle(4001); // canvas with transparent background
	c1 -> SetLogy(0);          // set log axis
	const Double_t XMIN   = 0.0;
	const Double_t XMAX   = 20.0;
	const Double_t XWIDTH = 0.1;

	Int_t bin = (Int_t)((XMAX - XMIN) / XWIDTH + 0.5);
	TH1D *h1 = new TH1D("h1", "", bin, XMIN, XMAX);
	h1 -> SetXTitle("Energy [XeV]");
	TH1D *h2 = new TH1D("h2", "", bin, XMIN, XMAX);
	TH1D *h3 = new TH1D("h3", "", bin, XMIN, XMAX);
	if (XWIDTH == 1.0)	 h1 -> SetYTitle("Events/XeV");
	else if(XWIDTH > 1.0)h1 -> SetYTitle(Form("Events/%.0fXeV", XWIDTH));
	else 								 h1 -> SetYTitle(Form("Events/%fXeV", XWIDTH));

	stringstream ss;

	double Xv,Yv,Zv,Px,Py,Pz;
	//double NuDirect[3]={-1.,0.,0.};
	double positronmom[3],neutronmom[3],E_nu;
	TVector3 Rpos, Vpos,EMom,NMom,NuDirect;
	rand0.SetSeed(0);
	rand1.SetSeed(0);
	rand2.SetSeed(0);
	rand3.SetSeed(0);
	rand4.SetSeed(0);
	rand5.SetSeed(0);

	init();

	Rpos.SetXYZ(ReactorX,ReactorY,ReactorZ);

	//ofstream wfile("data/NeutrinoGenR80_235_40000_003.dat");
	/*ss.str("");
	ss<<st.c_str()<<"_"<<NEVENT<<".dat";
	ofstream wfile(ss.str().c_str());
	ss.str("");
	ss<<st.c_str()<<"_"<<"epl"<<".dat";
	ofstream e_plus_write(ss.str().c_str());
	ss.str("");
	ss<<st.c_str()<<"_"<<"neu"<<".dat";
	ofstream neutron_write(ss.str().c_str());*/
	ss.str("");
	ss<<st.c_str()<<"_"<<"all"<<"_"<<NEVENT<<".dat";
	ofstream all_write(ss.str().c_str());

	for(int i=0;i<NEVENT;i++){
		//SetVertexPosition//
		Vpos=GetVertexPostion();

		//SetVertexMomentum//
		NuDirect=Vpos-Rpos;
		E_nu=GetNeutrinoMomentum(NuDirect,positronmom,neutronmom );
		EMom=TVector3(positronmom[0],positronmom[1],positronmom[2]);
		NMom=TVector3(neutronmom[0],neutronmom[1],neutronmom[2]);

		/*wfile<<setw(4)<<2   <<" "<<setw(10)<<E_nu    <<" "<<setw(10)<<Vpos.X()<<" "//u
		<<setw(10)<<Vpos.Y()<<" "<<setw(10)<<Vpos.Z()<<endl;
		wfile<<setw(4)<<-11 <<" "<<setw(10)<<EMom.X()<<" "<<setw(10)<<EMom.Y()<<" "//e-
		<<setw(10)<<EMom.Z()<<endl;
		wfile<<setw(4)<<2112<<" "<<setw(10)<<NMom.X()<<" "<<setw(10)<<NMom.Y()<<" "//neutron
		<<setw(10)<<NMom.Z()<<endl;*/
		//cerr << E_nu << endl;
		//cerr << numom.X()<< numom.Y() << numom.Z() << endl;
		//cerr << sqrt(numom.X()*numom.X()+numom.Y()*numom.Y()+numom.Z()*numom.Z())<< endl;

		double E_p = sqrt(EMom.X()*EMom.X()+EMom.Y()*EMom.Y()+EMom.Z()*EMom.Z());
		double E_n = sqrt(NMom.X()*NMom.X()+NMom.Y()*NMom.Y()+NMom.Z()*NMom.Z());
		//e_plus_write << E_p << endl;
		//neutron_write<< E_n << endl;
		all_write << E_nu << " " << E_p << " " << E_n << endl;
		//h1 -> Fill(E_nu);
		h1 -> Fill(E_nu);
		h2 -> Fill(E_p);
		h3 -> Fill(E_n);

		if(i%1000==0)cout<<i<<endl;
	}
	//wfile.close();
	h1 -> SetLineColor(1); // 2: red, 3: green, 4: blue
	h1 -> SetLineWidth(2);
	h1 -> Draw();
	h2 -> SetLineColor(2); // 2: red, 3: green, 4: blue
	h2 -> SetLineWidth(2);
	h2 -> Draw("same");
	h3 -> SetLineColor(4); // 2: red, 3: green, 4: blue
	h3 -> SetLineWidth(2);
	h3 -> Draw("same");
	string OutHistPDF = Form("En_hist_%d.pdf",NEVENT);
	c1 -> Print(OutHistPDF.c_str());
}
