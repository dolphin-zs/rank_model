#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include<string>
#include<stdlib.h>

using namespace std;

const unsigned int ML = 150;

string zsInt2String(int i){
    ostringstream ofs;
    ofs<<i;
    return ofs.str();
}

int min2(int t1, int t2){
	if(t1 <= t2)
		return t1;
	else
		return t2;
}

int min3(int t1, int t2, int t3){
	return min2(min2(t1, t2), t3);
}

void ldsalignment(vector<string>& f1, vector<string>& f2, vector<string>& ans){
	//cout<<"execute ldsalignment"<<endl;
	int lds_matrix[ML][ML];
	int row = f1.size();
	int col = f2.size();
	int i, j;

	for(i=0;i <= row;i++)
		lds_matrix[i][0] = i;
	for(j=0;j <= col;j++)
		lds_matrix[0][j] = j;
	for(i=1;i <= row;i++){
		for(j=1;j <= col;j++){
			if(f1[i-1] == f2[j-1])
				lds_matrix[i][j] = lds_matrix[i-1][j-1];
			else
				lds_matrix[i][j] = min3(lds_matrix[i-1][j-1]+1, lds_matrix[i][j-1]+1, lds_matrix[i-1][j]+1);
		}
	}

	vector<string>::iterator it;
	string temp_s;
	i = row;
	j = col;
	while((i>=1)&&(j>=1)){
		if(f1[i-1] == f2[j-1]){
			it = ans.begin();
			temp_s = f1[i-1] + " " + f2[j-1];
			ans.insert(it, temp_s);
			i--;
			j--;
		}
		else{
			if((lds_matrix[i][j-1]+1) == lds_matrix[i][j]){
				it = ans.begin();
				temp_s = "0 " + f2[j-1];
				ans.insert(it, temp_s);
				j--;
			}
			else if((lds_matrix[i-1][j]+1) == lds_matrix[i][j]){
				it = ans.begin();
				temp_s = f1[i-1] + " 0";
				ans.insert(it, temp_s);
				i--;
			}
			else if((lds_matrix[i-1][j-1]+1) == lds_matrix[i][j]){
				it = ans.begin();
				temp_s = f1[i-1] + " " + f2[j-1];
				ans.insert(it, temp_s);
				i--;
				j--;
			}
			else
				cerr<<"something wrong with lds_matrix["<<i<<"]["<<j<<"]\n";
		}
	}

	if((i==0) && (j==0)){}
	else if ((i==0) && (j!=0)){
		for(;j>=1;j--){
			it = ans.begin();
			temp_s = "0 " + f2[j-1];
			ans.insert(it, temp_s);
		}
	}
	else if ((i!=0) && (j==0)){
		for(;i>=1;i--){
			it = ans.begin();
			temp_s = f1[i-1] + " 0";
			ans.insert(it, temp_s);
		}
	}
	else
		cerr<<"something wrong in if row==0 && col==0"<<endl;

}



int main(int argc, char** argv){

	if(argc < 4){
		cerr<<"\n!!!arguments number error!!!"<<endl;
		cerr<<"please using format: "<<argv[0]<<" zh en en_tran\n";
		cerr<<endl;
		exit(1);
	}

	ifstream en_file(argv[1]);
	if(!en_file)
		cerr<<"cannot open file"<<argv[1]<<endl;
	ifstream fr_file(argv[2]);
	if(!fr_file)
		cerr<<"cannot open file"<<argv[2]<<endl;
	ifstream fr_tran_file(argv[3]);
	if(!fr_tran_file)
		cerr<<"cannot open file"<<argv[3]<<endl;

	int noSentence = 0;
	string en_line, fr_line, fr_tran_line;
	vector<string> en_vcblist(2, "NULL");
	vector<string> fr_vcblist(2, "NULL");
	map<string, int> en_vcbmap;
	map<string, int> fr_vcbmap;
	map<string, int> en_vcbfreq;
	map<string, int> fr_vcbfreq;

	ofstream of_lsda("zh_en_entran.lsda");
	ofstream of_en("zh.vcb");
	ofstream of_fr("en.vcb");

	cout<<"$$$Converting "<<argv[1]<<" "<<argv[2]<<" "<<argv[3];
  cout<<" from plain format to lsda format(zh_en_entran.lsda zh.vcb en.vcb)$$$"<<endl;

	while(getline(en_file, en_line) && getline(fr_file, fr_line) && getline(fr_tran_file, fr_tran_line)){
		vector<string> en_temp_sentence;
		vector<string> fr_temp_sentence;
		vector<string> fr_tran_temp_sentence;
    vector<string> lsda_temp_sentence;
		string temp_string;
		noSentence++;

		istringstream en_stringstream(en_line);
		while(en_stringstream>>temp_string){
			en_vcbfreq[temp_string]++;
			if(en_vcbmap.find(temp_string) == en_vcbmap.end()){
				en_vcblist.push_back(temp_string);
				en_vcbmap[temp_string] = en_vcblist.size() - 1;
			}
			en_temp_sentence.push_back(zsInt2String(en_vcbmap[temp_string]));
		}
		istringstream fr_stringstream(fr_line);
		while(fr_stringstream>>temp_string){
			fr_vcbfreq[temp_string]++;
			if(fr_vcbmap.find(temp_string) == fr_vcbmap.end()){
				fr_vcblist.push_back(temp_string);
				fr_vcbmap[temp_string] = fr_vcblist.size() - 1;
			}
			fr_temp_sentence.push_back(zsInt2String(fr_vcbmap[temp_string]));
		}
		istringstream fr_tran_stringstream(fr_tran_line);
		while(fr_tran_stringstream>>temp_string){
			fr_vcbfreq[temp_string]++;
			if(fr_vcbmap.find(temp_string) == fr_vcbmap.end()){
				fr_vcblist.push_back(temp_string);
				fr_vcbmap[temp_string] = fr_vcblist.size() - 1;
			}
			fr_tran_temp_sentence.push_back(zsInt2String(fr_vcbmap[temp_string]));
		}

    ldsalignment(fr_temp_sentence, fr_tran_temp_sentence, lsda_temp_sentence);

		if(en_temp_sentence.size() && fr_temp_sentence.size() && fr_tran_temp_sentence.size()){
			of_lsda<<noSentence<<"\n";

			for(vector<string>::iterator pt=en_temp_sentence.begin();pt != en_temp_sentence.end();pt++){
				of_lsda<<*pt<<" ";
			}
			of_lsda<<"\n";

			for(vector<string>::iterator pt=lsda_temp_sentence.begin();pt != lsda_temp_sentence.end();pt++){
				of_lsda<<*pt<<"  ";
			}
			of_lsda<<"\n";
		}
		else{
			cerr<<"error in "<<noSentence<<" sentence!"<<endl;
			exit(1);
		}
	}//end of while(getline())

	for(size_t i=2;i < en_vcblist.size();i++)
		of_en<<i<<" "<<en_vcblist[i]<<" "<<en_vcbfreq[en_vcblist[i]]<<"\n";
	for(size_t i=2;i < fr_vcblist.size();i++)
		of_fr<<i<<" "<<fr_vcblist[i]<<" "<<fr_vcbfreq[fr_vcblist[i]]<<"\n";

	return 0;
}
