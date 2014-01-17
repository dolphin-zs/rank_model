#ifndef SORTMODEL1
#define SORTMODEL1

#include "model12.h"

class SortModel1
{
	public:
		VcbList& EList;
		VcbList& FList;
		int Num;
		int noSent;
		string en_name;
		string fr_name;
		vector<vector<fs_logp> > logp_array;

		SortModel1(string e, string f, int n, VcbList& el, VcbList& fl):en_name(e), fr_name(f), Num(n), EList(el), FList(fl) {}
		void cal_logp();
		void sort_print();
};

#endif
