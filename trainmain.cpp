#undef  __DEPRECATED //neglect the warnings in using hash_map

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<cstdlib>
#include<limits.h>
#include<utility>

#include "gl_defs.h"
#include "vocab.h"
#include "rankmodel.h"
#include "buildrank.h"

using namespace std;


int main(int argc, char **argv)
{
  cout<<".........................RankModel Training........................."<<endl;
	if(argc < 4){
		cout<<"HELP: Please call "<<argv[0]<<" in this format: "<<argv[0]<<" en fr lsda_name "<<endl;
		exit(1);
	}

	string en_name(argv[1]);
	string fr_name(argv[2]);
	int N = 20;
  string lsda_name(argv[3]);
	string vcben_name = en_name + ".vcb";
	string vcbfr_name = fr_name + ".vcb";
	VcbList evcb(vcben_name.c_str());
	VcbList fvcb(vcbfr_name.c_str());
	fvcb.readVocalList();
	evcb.readVocalList();

	buildrank br_test(en_name, fr_name, N, evcb, fvcb);
	br_test.trainmodel(lsda_name.c_str());

	return 0;
}




