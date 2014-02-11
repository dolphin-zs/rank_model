#ifndef BUILDMODEL12
#define BUILDMODEL12

#include "model12.h"


class buildmodel12
{
  public:
    VcbList& EList;
    VcbList& FList;
    string en_name;
    string fr_name;
    int Num;
    vector<vector<fs_logp> > logp_array;

    buildmodel12(string e, string f, int N, VcbList& el, VcbList& fl): en_name(e), fr_name(f), Num(N), EList(el), FList(fl) {}
    void trainmodel1(const char* fn_snt);
    void decodemodel1(const char* fn_tfe);

    void sort_print(const char* fn_sort);

};


#endif
