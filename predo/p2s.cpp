#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include<string>
#include<stdlib.h>

using namespace std;

int main(int argc, char** argv){

	if(argc < 4){
		cerr<<"\n!!!arguments number error!!!"<<endl;
		cerr<<"please using format: "<<argv[0]<<" en fr fr_tran\n";
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

	ofstream of_snt("en_fr_frtran.snt");
	ofstream of_en_fr("en_frtran.snt");
	ofstream of_en("en.vcb");
	ofstream of_fr("fr.vcb");

	cout<<"$$$Converting "<<argv[1]<<" "<<argv[2]<<" "<<argv[3]<<" from plain format to snt format(en_fr_frtran.snt en_fr.snt en.vcb fr.vcb).$$$"<<endl;

	while(getline(en_file, en_line) && getline(fr_file, fr_line) && getline(fr_tran_file, fr_tran_line)){
		vector<string> en_temp_sentence;
		vector<string> fr_temp_sentence;
		vector<string> fr_tran_temp_sentence;
		string temp_string;
		noSentence++;

		istringstream en_stringstream(en_line);
		while(en_stringstream>>temp_string){
			en_vcbfreq[temp_string]++;
			en_temp_sentence.push_back(temp_string);
			if(en_vcbmap.find(temp_string) == en_vcbmap.end()){
				en_vcblist.push_back(temp_string);
				en_vcbmap[temp_string] = en_vcblist.size() - 1;
			}
		}
		istringstream fr_stringstream(fr_line);
		while(fr_stringstream>>temp_string){
			fr_vcbfreq[temp_string]++;
			fr_temp_sentence.push_back(temp_string);
			if(fr_vcbmap.find(temp_string) == fr_vcbmap.end()){
				fr_vcblist.push_back(temp_string);
				fr_vcbmap[temp_string] = fr_vcblist.size() - 1;
			}
		}
		istringstream fr_tran_stringstream(fr_tran_line);
		while(fr_tran_stringstream>>temp_string){
			fr_vcbfreq[temp_string]++;
			fr_tran_temp_sentence.push_back(temp_string);
			if(fr_vcbmap.find(temp_string) == fr_vcbmap.end()){
				fr_vcblist.push_back(temp_string);
				fr_vcbmap[temp_string] = fr_vcblist.size() - 1;
			}
		}

		if(en_temp_sentence.size() && fr_temp_sentence.size() && fr_tran_temp_sentence.size()){
			of_snt<<noSentence<<"\n";
			of_en_fr<<noSentence<<"\n";

			for(vector<string>::iterator pt=en_temp_sentence.begin();pt != en_temp_sentence.end();pt++){
				of_snt<<en_vcbmap[*pt]<<" ";
				of_en_fr<<en_vcbmap[*pt]<<" ";
			}
			of_snt<<"\n";
			of_en_fr<<"\n";

			for(vector<string>::iterator pt=fr_temp_sentence.begin();pt != fr_temp_sentence.end();pt++)
				of_snt<<fr_vcbmap[*pt]<<" ";
			of_snt<<"\n";

			for(vector<string>::iterator pt=fr_tran_temp_sentence.begin();pt != fr_tran_temp_sentence.end();pt++){
				of_snt<<fr_vcbmap[*pt]<<" ";
				of_en_fr<<fr_vcbmap[*pt]<<" ";
			}
			of_snt<<"\n";
			of_en_fr<<"\n";
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
