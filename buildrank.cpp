
#include "buildrank.h"

void buildrank::buildmodel(const char* in_file){

  cout<<"......Building RankModel......"<<endl;

	RankModel test_rank(EList, FList);
	test_rank.readcorpus(in_file);
	test_rank.train_init2();
	test_rank.em_algo2(5);
  test_rank.print_tffe("t_ffe.prob");
  test_rank.decode_init(en_name, fr_name, Num, logp_array);
  test_rank.decoding(en_name, fr_name, Num, logp_array);

  cout<<"......Building END......."<<endl;

}

void buildrank::trainmodel(const char* in_file){

  cout<<"......Training RankModel......"<<endl;

  RankModel test_rank(EList, FList);
  test_rank.readcorpus(in_file);
  test_rank.train_init2();
  test_rank.em_algo2(5);
  test_rank.print_tffe("t_ffe.prob");

  cout<<"......Training END......"<<endl;

}

void buildrank::multibuild(const char* in_file){

  cout<<"......Building RankModel......"<<endl;
	RankModel test_rank(EList, FList);
	test_rank.readcorpus(in_file);
	test_rank.train_init2();
	test_rank.em_algo2(5);
  //test_rank.print_tffe("t_ffe.prob");
  test_rank.decode_init(en_name, fr_name, 20, logp_array);
  for(int i=2;i <= Num;i+=2){
    string fsname = fr_name + "_rank.sort" + zsInt2String(i);
    test_rank.decoding(en_name, fr_name, i, logp_array);
    multisort_print(i, fsname.c_str());
  }

  cout<<"......Building END......."<<endl;

}

void buildrank::decodemodel(const char* in_tffe){

    cout<<"......Decoding RankModel......"<<endl;
    RankModel test_rank(EList, FList);
    test_rank.Decoder(en_name, fr_name, Num, logp_array, in_tffe);
    cout<<"......Decoding END......"<<endl;

}

void buildrank::buildmodel_old(const char* in_file){
	RankModel test_rank(EList, FList);
	test_rank.readcorpus(in_file);
	test_rank.train_init2();
	test_rank.em_algo2(5);
	vector<fs_logp> st;
	logp_array.push_back(st);
	for(int i=1;i <= Num;i++){
		logp_array.push_back(st);
		for(int j=1;j <= Num;j++){
			if(i != j){
				string lsda_name = fr_name + zsInt2String(i) + "_" + zsInt2String(j) + ".lsda";
				cout<<"manipulating the "<<lsda_name<<endl;

				test_rank.decode2(en_name, lsda_name, i, logp_array[i]);

			}
		}
	}
}

void buildrank::sort_print(const char* fn_sort){
  cout<<"......print sort information to file ......"<<fn_sort<<endl;
	ofstream of_sort(fn_sort);
	unsigned int noSent = logp_array[1].size();//logp_array[0].size();

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

void buildrank::multisort_print(int kk, const char* fn_sort){
  cout<<"......print sort information to file ......"<<fn_sort<<endl;
	ofstream of_sort(fn_sort);
	unsigned int noSent = logp_array[1].size();//logp_array[0].size();

	for(unsigned int j=0;j < noSent;j++){
		vector<fs_logp> temp_fl;
		for(int i=1;i <= kk;i++)
			temp_fl.push_back(logp_array[i][j]);

		sort(temp_fl.begin(), temp_fl.end());
		of_sort<<(j+1)<<"\n";
		for(vector<fs_logp>::iterator it=temp_fl.begin();it != temp_fl.end();it++)
			of_sort<<(*it).nof<<"( "<<(*it).logp<<" ) ";
		of_sort<<"\n";
	}
  cout<<"there are "<<noSent<<" in total."<<endl;
  cout<<"......print end ......"<<endl;

}
