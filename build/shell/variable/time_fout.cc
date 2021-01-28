//root -x -l -q time_fout.cc
//. time.dat
//root -l 'root.cc("../shell/'TIME'.root")'
//2019/11/18

#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <time.h>

using namespace std;

void time_fout(){
	stringstream ss;
	ss.str("");
	ss<<"variable/";
	ss<<"time.dat";
	ofstream fout(ss.str());
	struct tm tm;
	time_t t = time(NULL);
	localtime_r(&t, &tm);
	fout<<"TIME=\""<< std::to_string( (tm.tm_year + 1900)*1000000 +
														 (tm.tm_mon+1)*10000 + (tm.tm_mday)*100 +(tm.tm_hour))
			<<"\""<<endl;
}
int main(){
	time_fout();
	return 0;
}
