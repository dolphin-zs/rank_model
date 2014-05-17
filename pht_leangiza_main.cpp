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

using namespace std;


int main(int argc, char **argv)
{
  cout<<".........................Phrase-table modifying........................."<<endl;
	if(argc < 5){
		cout<<"HELP: Please call "<<argv[0]<<" in this format: "<<argv[0]<<" en fr t_ffe.prob phrase-table_name "<<endl;
		exit(1);
	}

	string en_name(argv[1]);
	string fr_name(argv[2]);
  string tffe_name(argv[3]);
  string pht_name(argv[4]);
	string vcben_name = en_name + ".vcb";
	string vcbfr_name = fr_name + ".vcb";
	VcbList evcb(vcben_name.c_str());
	VcbList fvcb(vcbfr_name.c_str());
	fvcb.readVocalList();
	evcb.readVocalList();

  RankModel phtm_test(evcb, fvcb);
  map<string, vector<vector<string> > > pht_map;
  phtm_test.phrasetable_learngiza( pht_map, tffe_name.c_str(), pht_name.c_str(), "phrase-table.learngiza++");
  cout<<".................................END....................................."<<endl;


	return 0;
}




