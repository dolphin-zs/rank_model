#ifndef RANKMODEL
#define RANKMODEL

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

extern string zsInt2String(int i);
extern void lsdalignment(const vector<string>& f1, const vector<string>& f2, vector<string>& ans);


class hashfunc: public unary_function< pair<WordIndex, WordIndex>, size_t>
{
	public:
		size_t operator() (const pair<WordIndex, WordIndex>& key) const
		{
			return (size_t)MAX_W*key.first+key.second;
		}
};

class CPPair{
	public:
		double count;
		double prob;
		CPPair():count(0),prob(0){}
		CPPair(double c, double p):count(c), prob(p){}
};

class FPair{
	public:
		WordIndex f_id;
		WordIndex ft_id;
		FPair():f_id(0), ft_id(0){}
		FPair(WordIndex i, WordIndex j):f_id(i), ft_id(j){}
};
class RankSent{
	public:
		int noSent;
		vector<WordIndex> esent;
		vector<FPair> ffsent;
		RankSent(){}
		void clear(){
			esent.clear();
			ffsent.clear();
			noSent = 0;
		}
};

class FFEPair{
	public:
		WordIndex fr_id;
		WordIndex frtr_id;
		WordIndex en_id;

		FFEPair(WordIndex i, WordIndex j, WordIndex k):fr_id(i), frtr_id(j), en_id(k){}
		size_t getindex() const{
			return (size_t)fr_id*MAX_W*MAX_W + frtr_id*MAX_W + en_id;
		}
};
class hash_ffe{
	public:
		size_t operator()(const class FFEPair& x) const{
			return x.getindex();
		}
};
class equal_ffe{
	public:
		bool operator()(const class FFEPair& x, const class FFEPair& y) const{
			return (x.getindex() == y.getindex());
		}
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


class RankModel{
	public:
		VcbList& EList;
		VcbList& FList;
		vector<RankSent> rankcorpus;
    vector<vector<WordIndex> > decode_en;
    vector<vector<vector<string> > > decode_frarr;
    vector<vector<FPair> > decode_ff;

		hash_map<FFEPair, CPPair, hash_ffe, equal_ffe> info_ffe;
		hash_map<WordPairIds, CPPair, hashfunc, equal_to<WordPairIds> > info_fe;
		hash_map<FFEPair, CPPair, hash_ffe, equal_ffe> t_ffe;
		map<WordIndex, double> count_e;

		RankModel(VcbList& en, VcbList& fr):EList(en), FList(fr){}
		void readcorpus(const char* in_file);

    //rankmodel train 1
		void train_init1();
		void em_algo1(int noIterations);
		void cal_tffe1(const char* ptc);

    //rankmodel train 2
    void train_init2();
		void em_algo2(int noIterations);

    //decode function
    void read_tffe(const char* fn_tffe);
    void decode_init(string en, string fr, int N, vector<vector<fs_logp> >& logp_record);
    void decoding(string en, string fr, int N, vector<vector<fs_logp> >& logp_record);
    void Decoder(string en, string fr, int N, vector<vector<fs_logp> >& logp_record, const char* fn_tffe);
    void Decoder_na(string en, string fr, int N, vector<vector<fs_logp> >& logp_record, const char* fn_tffe, const char* fn_tst_ff);

    //output function
    void print_tffe(const char* fn_tffe);

    //old function
		void decode2(string en_name, string lsda_name, int no, vector<fs_logp>& ffe_logp);
		void print_align(ofstream& of);
		void cal_logp(int no, vector<fs_logp>& ffe_logp);
};

#endif
