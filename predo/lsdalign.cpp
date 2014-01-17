#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include<string>
#include<stdlib.h>

using namespace std;

const unsigned int ML = 150;

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
	cout<<"execute ldsalignment"<<endl;
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
	if(argc < 2){
		cerr<<"\nusing format: "<<argv[0]<<" en_fr_frtran.snt.\n"<<endl;
		exit(1);
	}

	ifstream in_fftran(argv[1]);
	if(!in_fftran)
		cerr<<"cannot open file "<<argv[1]<<" !"<<endl;
	ofstream of_ldsa("en_fr_frtran.ldsa");

	string line_no, line_en, line1, line2;
	string temp_i;
	while(getline(in_fftran, line_no) && getline(in_fftran, line_en) && getline(in_fftran, line1) && getline(in_fftran, line2)){
		vector<string> f1_sent;
		vector<string> f2_sent;
		vector<string> lds_sent;

		istringstream f1_buffer(line1);
		while(f1_buffer>>temp_i)
			f1_sent.push_back(temp_i);

		istringstream f2_buffer(line2);
		while(f2_buffer>>temp_i)
			f2_sent.push_back(temp_i);

		ldsalignment(f1_sent, f2_sent, lds_sent);

		of_ldsa<<line_no<<"\n";
		of_ldsa<<line_en<<"\n";
		for(vector<string>::iterator it = lds_sent.begin();it != lds_sent.end();it++)
			of_ldsa<<*it<<"  ";
		of_ldsa<<"\n";
	}

	return 0;
}

