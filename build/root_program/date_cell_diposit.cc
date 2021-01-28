// $ root -b -l -q 'geant_data_cut.cc("data")'
//  -b batch mode  -l no interpreter  -q quit at finish

//

void familytree_test2(const std::string ifile){
  #include <iostream>
  #include <sstream>
  #include <fstream>
  #include <string.h>
  #include <iomanip>

  // open file
  string fin_dir = "data/";
  string fout_dir = "data_cut/";
  stringstream ss;
  ss.str("");
  //ss<<fin_dir.c_str()<<ifile.c_str()<<".dat";
  //cout<<"File_in->"<<fin_dir.c_str()<<ifile.c_str()<<".dat"<<endl;
  ss <<ifile.c_str()<<".dat";
  cout<<"File_in ->"<<ifile.c_str()<<".dat"<<endl;
  ifstream fin(ss.str());

  if (!fin) {
    cerr << "Error: don't exist such a data file, " << ss.str() << " !" << endl;
    //return -1;
    //break;
  }

  const double Det_Size_x = 1000; //mm
  const double Det_Size_y = 1000;
  const double Det_Size_z = 1000;

  int EventID;
  int ParentID;
  int TrackID;
  string ParticleName;
  double Positionx, Positiony, Positionz;
  //double PosPositionx, PosPositiony, PosPositionz;
  double VertexKineticEnergy;
  double KineticEnergy;
  double TotalEnergyDeposit;//deposit to volume
  double Time;
  string PreProcessName;
  string PostProcessName;
  string OriginedProcessName;

  string ParName;
  string CopyNo;

  string line;

  ss.str("");
  ss<<"data_hoge";
  ss<<".dat";
  cout<<"File_out->"<<ss.str()<<" :data"<<endl;
  ofstream dout(ss.str());

  while (getline(fin, line)) {
    if (line.empty() || (line[0] == '#')) {
      continue;
    }

    if (!(istringstream(line) >> EventID >> ParentID
    //>> ParName
    >> TrackID
    >> ParticleName
    >> CopyNo
    >> Positionx >> Positiony	>> Positionz
    >> PosPositionx >> PosPositiony	>> PosPositionz
    >> VertexKineticEnergy
    >> KineticEnergy
    >> TotalEnergyDeposit
    >> Time
    >> PreProcessName
    >> PostProcessName
    >> OriginedProcessName)) {
      cerr << "Error: badly formatted data line: " << line << endl;
      //return -1;
      break;
    }


  }
}
