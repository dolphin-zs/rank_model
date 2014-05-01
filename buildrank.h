#ifndef BUILDRANK
#define BUILDRANK

#include "rankmodel.h"

class buildrank
{
	public:
		VcbList& EList;
		VcbList& FList;
		string en_name;
		string fr_name;
		int Num;
		vector<vector<fs_logp> > logp_array;

		buildrank(string e, string f, int N, VcbList& el, VcbList& fl):en_name(e), fr_name(f), Num(N), EList(el), FList(fl) {}
    void buildmodel(const char* in_file);
		void buildmodel_old(const char* in_file);

    void trainmodel(const char* in_file);
    void decodemodel(const char* in_tffe);
    void decodemodel_na(const char* in_tffe, const char* in_tst_ff);

		void sort_print(const char* fn_sort);
    void multibuild(const char* in_file);
    void multisort_print(int kk, const char* fn_sort);
};


#endif
