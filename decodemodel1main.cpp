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
#include "sentence.h"
#include "model12.h"
#include "buildmodel12.h"

using namespace std;


int main(int argc, char **argv)
{
  cout<<".........................IBM Model Decoding........................."<<endl;
	if(argc < 5){
		cout<<"HELP: Please call "<<argv[0]<<" in this format: "<<argv[0]<<" en fr N tfe_name "<<endl;
		exit(1);
	}

	string en_name(argv[1]);
	string fr_name(argv[2]);
	int N = atoi(argv[3]);
  string tfe_name(argv[4]);

	string vcben_name = en_name + ".vcb";
	string vcbfr_name = fr_name + ".vcb";
	VcbList evcb(vcben_name.c_str());
	VcbList fvcb(vcbfr_name.c_str());
	evcb.readVocalList();
	fvcb.readVocalList();

  string sort_name = "en_model1.sort";
	buildmodel12 bm1_test(en_name, fr_name, N, evcb, fvcb);
  bm1_test.decodemodel1(tfe_name.c_str());
	bm1_test.sort_print(sort_name.c_str());

	return 0;
}




