/*vocabulary list file*/

#ifndef VOCAB_H
#define VOCAB_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h> // exit() function
#include "gl_defs.h"

using namespace std;

class WordEntry
{
	public:
		string word;
		double freq;
		WordEntry():word("\0"), freq(0){};
		WordEntry(string s, int f):word(s), freq(f){};
};

class VcbList
{
	private:
		vector<WordEntry> volist;
		map<string, int> s2i;
		double total;
		WordIndex noUniqueTokens;
		const char* filename;
	public:
		VcbList(const char* p):volist(), total(0), noUniqueTokens(0), filename(p){}
		VcbList(const VcbList& a):volist(a.volist), s2i(a.s2i), total(a.total), noUniqueTokens(a.noUniqueTokens), filename(a.filename){}
		void setName(const char* p) { filename = p; }
		inline WordIndex size() const { return volist.size(); }
		inline WordIndex uniqTokens() const { return noUniqueTokens; }
		inline double totalVocab() const { return total; }
		inline vector<WordEntry>& getVocalList() { return volist; }
		int operator[](const string& x) const{
			map<string, int>::const_iterator it = s2i.find(x);
			if(it != s2i.end())
				return it->second;
			else{
				//cout<<"ERROR: no word index for "<<x<<endl;
				return 1;
			}
		}
		const string operator[](WordIndex id){
			if(id < volist.size())
				return volist[id].word;
			else{
				cerr<<"ERROR: id is illegal. id: "<<id<<endl;
				return 0;
			}
		}
		void readVocalList();
};

#endif
