
#include "sortrank.h"

string zsInt2String(int i){
    ostringstream buf;
    buf<<i;
    return buf.str();
}

void SortRank::cal_logp(){
	vector<fs_logp> st;
	//st.push_back(fs_logp());
	logp_array.push_back(st);
	for(int i=1;i <= Num;i++){
		logp_array.push_back(st);
		for(int j=1;j <= Num;j++){
			if(i != j){
				RankModel temp_rm(EList, FList);
				string infile_name = en_name + fr_name + zsInt2String(i) + "_" + zsInt2String(j) + ".lsda";

				temp_rm.readcorpus(infile_name.c_str());
				temp_rm.initialization();
				temp_rm.em_algo1(5);
				temp_rm.cal_logp(i, logp_array[i]); 

			} 
		}
		noSent = logp_array[i].size();
	}
}

void SortRank::sort_print(){
	string of_name = fr_name + "_rank.sort";
	ofstream of_sort(of_name.c_str());

	for(unsigned int j=0;j < noSent;j++){
		vector<fs_logp> temp_fl;
		for(int i=1;i <= Num;i++)
			temp_fl.push_back(logp_array[i][j]);

		sort(temp_fl.begin(), temp_fl.end());
		of_sort<<(j+1)<<"\n";
		for(vector<fs_logp>::iterator it=temp_fl.begin();it != temp_fl.end();it++)
			of_sort<<(*it).nof<<"( "<<(*it).logp<<" ) ";
		of_sort<<"\n";
	}

}





