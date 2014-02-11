

#include "buildmodel12.h"


void buildmodel12::trainmodel1(const char* fn_snt){
  cout<<"......Training IBM model 1......"<<endl;

  model12 tmodel(EList, FList);
  tmodel.train_init(fn_snt);
  tmodel.em_algo1(5);
  tmodel.print_tfe("t_fe.prob");

  cout<<"......Training END......"<<endl;

}


void buildmodel12::decodemodel1(const char* fn_tfe){
  cout<<"......Decoding IBM model 1......"<<endl;

  model12 tmodel(EList, FList);
  tmodel.Decoder1(en_name, fr_name, Num, fn_tfe, logp_array);

  cout<<"......Decoding END......"<<endl;

}


void buildmodel12::sort_print(const char* fn_sort){
  cout<<"......print sort information to file ......"<<fn_sort<<endl;
	ofstream of_sort(fn_sort);
	unsigned int noSent = logp_array[1].size();

	for(unsigned int j=0;j < noSent;j++){
		vector<fs_logp> temp_fl;
		for(int i=1;i <= Num;i++)
			temp_fl.push_back(logp_array[i][j]);

		sort(temp_fl.begin(), temp_fl.end());
		of_sort<<(j+1)<<"\n";
		for(vector<fs_logp>::iterator it=temp_fl.begin();it != temp_fl.end();it++)
			of_sort<<(*it).nof<<"( "<<log( (*it).logp )<<" ) ";
		of_sort<<"\n";
	}
  cout<<"there are "<<noSent<<" in total."<<endl;
  cout<<"......print end ......"<<endl;

}



