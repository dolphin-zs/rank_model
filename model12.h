/*model 1 2 file*/

#ifndef MODEL12_H
#define MODEL12_H

#undef  __DEPRECATED
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
#include<math.h>
#include<algorithm>

#if __GNUC__>2
#include <ext/hash_set>
#include <ext/hash_map>
using namespace __gnu_cxx;
#else
#include <hash_set>
#include <hash_map>
using namespace stdext;
#endif

#include "gl_defs.h"
#include "vocab.h"
#include "sentence.h"

using namespace std;

class hashpair: public unary_function< pair<WordIndex, WordIndex>, size_t>
{
	public:
		size_t operator() (const pair<WordIndex, WordIndex>& key) const
		{
			return (size_t)MAX_W*key.first+key.second;
		}
};

class CPPair
{
	public:
		double count;
		double prob;
		CPPair():count(0),prob(0){}
		CPPair(double c, double p):count(c), prob(p){}
};

class fs_logp{
	public:
		int nof;
		double logp;
		fs_logp(int k=0, double p=0):nof(k), logp(p){}
		fs_logp(const fs_logp& qq): nof(qq.nof), logp(qq.logp) {}
		bool operator < (const fs_logp& yy) const{
			return (logp > yy.logp);
		}
};


class model12
{
	public:
		VcbList& EList;
		VcbList& FList;
		SentenceHandle sHander;
    vector<vector<WordIndex> > decode_en;
    vector<vector<vector<WordIndex> > > decode_frarr;

		hash_map<WordPairIds, CPPair, hashpair, equal_to<WordPairIds> > cal_ef;
		map<WordIndex, double> count_e;
		map<WordIndex, double> count_jilm;
		map<WordIndex, double> count_ilm;
		map<WordIndex, double> count_jlm;
		map<WordIndex, double> q_jilm;

		model12(VcbList& el, VcbList& fl): EList(el), FList(fl) {}
    //IBM model train
		void train_init(const char* fn_snt);
		void em_algo1(int noIterations);//model 1 algorithm
		void em_algo2(int noIterations);//model 2 algorithm

    //IBM model 1 decode
    void decode_init1(string en, string fr, int N, const char* fn_tfe);
    void decoding1(string en, string fr, int N, vector<vector<fs_logp> >& logp_record);
    void Decoder1(string en, string fr, int N, const char* fn_tfe, vector<vector<fs_logp> >& logp_record);

    //output function
		void print_tfe(const char* fn_tfe);

    //old function
		void print_align(ofstream& of);
		void cal_logp(int no, vector<fs_logp>& fe_logp);
};

#endif
