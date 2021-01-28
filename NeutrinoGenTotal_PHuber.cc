
#define ReactorX 24.//m
#define ReactorY 0.
#define ReactorZ 0.

#define DetectorX 1.//m
#define DetectorY 0.1//m
#define DetectorZ 0.2//m

//#define DetectorRad 0.6 //m
//#define DetectorSylHeight 0.6 //m

/*Joyo
#define FRateU235 0.371
#define FRateU238 0.073
#define FRatePu239 0.513
#define FRatePu241 0.043
*/

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

/*
TVector3 GetVertexPostion (void)
{
 double xv,yv,zv,flag;
 TVector2 tpos; 
 TVector3 vpos,vpos1;

 do{
     xv=DetectorRad*(2.*rand0.Rndm()-1.);
     yv=DetectorRad*(2.*rand1.Rndm()-1.);
     zv=(DetectorSylHeight/2.)*(2.*rand2.Rndm()-1.);
     vpos=TVector3(xv,yv,zv);
     vpos1=TVector3(xv,yv,fabs(zv)-DetectorSylHeight/2.);
     tpos=TVector2(xv,yv);
     if(fabs(zv)<=DetectorSylHeight/2.)flag=0;
     if(fabs(zv)>DetectorSylHeight/2.)flag=1;

     //}while(!((flag==0&&tpos.Mod()<=DetectorRad)||(flag==1&&vpos1.Mag()<=DetectorRad)));

 }while(vpos.Perp()>DetectorRad||fabs(zv)>DetectorSylHeight/2.);
 return vpos;

} 
*/

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

double CalNeutrinoSpectrum(double E_nu, double cos_theta)
{ 
  //double E_nu=x[0];
  //double cos_theta=x[1];

 const double dM = M_n - M_p;//MeV
 const double M = (M_p+M_n)/2;//MeV
 const double f = 1.0;
 const double g = 1.267;
 const double sigma0 = 0.952e-42/(f*f+3*g*g);
 const double f2 = 3.706;//mu_p - mu_n  
 const double y2 = (dM*dM - m_e*m_e)/2.;

 /*
 const int NDimention =7;
 //const double fU235[]={2.70156, -5.90054, 4.67757, -1.11063, -0.0789809, 0.0660638, 0.00211228,
 //                      -0.00177409, 0.000104067, 4.10544, -2.22289, 0.0437163};
 const double fU235[]={3.1882, -0.70654, -0.336322, 0.110402, 0.00307667, -0.00373764, 0.000309321, 
                       5.30531, -1.41786};//pol7+exp2(Emin=1.5,Emid=6,Emax=8)
 const double fU238[]={4.13676, -1.6741, 0.127912, 0.0297204, -0.00194553, -0.000846528, 8.67637e-05, 
                       4.78605, -1.26563};//pol7+exp2(Emin=1.5,Emid=6,Emax=8)
 const double fPu239[]={3.37978, -1.48562, 0.12359, 0.0270622, -0.00185714, -0.000777481, 7.96712e-05, 
                       5.64435, -1.55669};//pol7+exp2(Emin=1.5,Emid=6,Emax=8)
 const double fPu241[]={3.05987, -0.579083, -0.333624, 0.0967984, 0.0037107, -0.00323844, 0.000255672, 
                        5.43431, -1.45546};//pol7+exp2(Emin=1.5,Emid=6,Emax=8)
 */

 double rate235=0.; 
 double rate238=0.;
 double rate239=0.;
 double rate241=0.;

 /*
 if(E_nu<=EMID){
 for(int nd=0;nd<NDimention;nd++){
   rate235+=fU235[nd]*pow(E_nu,nd);
   rate238+=fU238[nd]*pow(E_nu,nd);
   rate239+=fPu239[nd]*pow(E_nu,nd);
   rate241+=fPu241[nd]*pow(E_nu,nd);
 }
 }

 if(E_nu>EMID){
   rate235=exp(fU235[NDimention]+fU235[NDimention+1]*E_nu);
   rate238=exp(fU238[NDimention]+fU238[NDimention+1]*E_nu);
   rate239=exp(fPu239[NDimention]+fPu239[NDimention+1]*E_nu);
   rate241=exp(fPu241[NDimention]+fPu241[NDimention+1]*E_nu);
 }
 */
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
  //nudirect=TVector3(nudi[0],nudi[1],nudi[2]);
 
  double E_nu, phi, theta, cos_theta;
  double nu,ans,maxans,rate;
    
  do{
     maxans=CalNeutrinoSpectrum(3.5,-1);
     
     E_nu=rand3.Rndm()*(EMAX-1.806)+1.806;
     //cout << "nutron Energy = " << E_nu << endl;
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
  //cout << "e+ Energy = " << Ee << endl;
  En=sqrt(E_nu*E_nu-2.*E_nu*Ee*cos_theta+Ee*Ee);
  //cout << "Neutrino Energy = " << En << endl;
  cos_alpha=(E_nu-Ee*cos_theta)/En;
  alpha=acos(cos_alpha);

  emom.SetXYZ(Ee*sin(theta)*cos(phi),Ee*sin(theta)*sin(phi),Ee*cos(theta));
  nmom.SetXYZ(En*sin(alpha)*cos(phi+TMath::Pi()),En*sin(alpha)*sin(phi+TMath::Pi()),En*cos(alpha));
  //emom=Ee/nudirect.Mag()*nudirect;
  //nmom=En/nudirect.Mag()*nudirect;

  //cout<<theta<<" "<<phi<<" "<<alpha<<endl;
  //cout<<emom.X()/nudirect.X()<<" "<<emom.Y()/nudirect.Y()<<endl;

  emom.RotateY(acos(nudirect.Z()/nudirect.Mag()));
  emom.RotateZ(acos(nudirect.X()/nudirect.Perp()));
  fPositronMomemtum.SetXYZ(emom.X(),emom.Y(),emom.Z());

  nmom.RotateY(acos(nudirect.Z()/nudirect.Mag()));
  nmom.RotateZ(acos(nudirect.X()/nudirect.Perp()));
  fNeutronMomemtum.SetXYZ(nmom.X(),nmom.Y(),nmom.Z());

  //fPositronMomemtum.Rotate(theta, vv);
  //fPositronMomemtum.Rotate(theta, emom);
  //fPositronMomemtum.Rotate(phi, emom);

   //cout<<fPositronMomemtum.X()<<" "<<emom.X()<<endl;
 
  //fNeutronMomemtum = nmom;
  //fNeutronMomemtum.Rotate(alpha, vv);
  //fNeutronMomemtum.Rotate(alpha, nmom);
  //fNeutronMomemtum.Rotate(phi+TMath::Pi(), nmom);

  posimom[0]=fPositronMomemtum.X();
  posimom[1]=fPositronMomemtum.Y();
  posimom[2]=fPositronMomemtum.Z();

  neutronmom[0]=fNeutronMomemtum.X();
  neutronmom[1]=fNeutronMomemtum.Y();
  neutronmom[2]=fNeutronMomemtum.Z();

  return E_nu;
}




void NeutrinoGenTotal_PHuber(string st, int NEVENT)
{
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
 ss.str("");
 ss<<st.c_str()<<"_"<<NEVENT<<".dat";
 ofstream wfile(ss.str().c_str());

 for(int i=0;i<NEVENT;i++){
  //SetVertexPosition//
  Vpos=GetVertexPostion();

  //SetVertexMomentum//
  NuDirect=Vpos-Rpos;
  E_nu=GetNeutrinoMomentum(NuDirect,positronmom,neutronmom );
  cout << E_nu << endl;
  EMom=TVector3(positronmom[0],positronmom[1],positronmom[2]);
  NMom=TVector3(neutronmom[0],neutronmom[1],neutronmom[2]);
 
  wfile<<2<<" "<<E_nu<<" "<<Vpos.X()<<" "<<Vpos.Y()<<" "<<Vpos.Z()<<endl;
  wfile<<-11<<" "<<EMom.X()<<" "<<EMom.Y()<<" "<<EMom.Z()<<endl;
  wfile<<2112<<" "<<NMom.X()<<" "<<NMom.Y()<<" "<<NMom.Z()<<endl;
  if(i%1000==0)cout<<i<<endl;
 }

 wfile.close();


}
