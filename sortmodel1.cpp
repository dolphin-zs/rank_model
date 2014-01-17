
#include "sortmodel1.h"

string zsInt2String(int i){
    ostringstream buf;
    buf<<i;
    return buf.str();
}

void SortModel1::cal_logp(){
	vector<fs_logp> st;
	logp_array.push_back(st);
	for(int i=1;i <= Num;i++){
		logp_array.push_back(st);
		string snt_file = en_name + "_" + fr_name + zsInt2String(i) + ".snt";
		SentenceHandle shandle(snt_file.c_str());
		noSent = shandle.noSentInBuffer;

		model12 temp_m1(EList, FList, shandle);
		temp_m1.initialization();
		temp_m1.em_algo1(5);
		temp_m1.cal_logp(i, logp_array[i]);
	}
}

void SortModel1::sort_print(){
	string of_name = fr_name + "_model1.sort";
	ofstream of_sort(of_name.c_str());

	for(int j=0;j < noSent;j++){
		vector<fs_logp> temp_logp;
		for(int i=1;i <= Num;i++)
			temp_logp.push_back(logp_array[i][j]);

		sort(temp_logp.begin(), temp_logp.end());

		of_sort<<(j+1)<<"\n";
		for(vector<fs_logp>::iterator pt=temp_logp.begin();pt != temp_logp.end();pt++)
			of_sort<<(*pt).nof<<"( "<<(*pt).logp<<" ) ";
		of_sort<<"\n";
	}
		
}


			



