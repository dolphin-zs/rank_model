/*sentence file*/

#ifndef SENTENCE_H
#define SENTENCE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h> // exit() function
#include "gl_defs.h"


class SentPair
{
	public:
		int sentenceNo;
		vector<WordIndex> esent;
		vector<WordIndex> fsent;
		float noOcc;

		SentPair(){}
		void clear(){
			esent.clear();
			fsent.clear();
			sentenceNo = 0;
			noOcc = 0;
		}
		const vector<WordIndex>& get_esent() const{
			return esent;
		}
		const vector<WordIndex>& get_fsent() const{
			return fsent;
		}
		int getSentenceNo() const{
			return sentenceNo;
		}
};

class SentenceHandle
{
	public:
		const char* filename;
		ifstream* p_inputFile;
		vector<SentPair> sent_buffer;
		int currentSentence;
		int noSentInBuffer;
		int pair_no;
		int totalPair;

		SentenceHandle(const char* fn);
		void new_start();
		bool getNextSentence(SentPair&);
		bool readNextSentence(SentPair&);
};

#endif
