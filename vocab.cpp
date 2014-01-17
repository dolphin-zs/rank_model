
#include "vocab.h"

void VcbList::readVocalList()
{
	int freq = 0;
	WordIndex word_id;
	WordEntry entry("NULL", 0);
    string line, word;
	cout<<"Reading vocabulary file from: "<<filename<<"\n";
	ifstream vlFile(filename);
	if(!vlFile){
		cerr<<"\nCannot open vocabulary file "<<filename<<"\n";
		exit(1);
	}
	volist.push_back(entry);
	s2i[entry.word] = volist.size() - 1;
	entry.word = "@@:@@";
	entry.freq = 0;
	volist.push_back(entry);
	s2i[entry.word] = 1;
	noUniqueTokens = 1;

	while(getline(vlFile, line)){
		istringstream word_buffer(line);
		if(!(word_buffer>>word_id>>word>>freq))
			cerr<<"ERROR: reading vocabulary; "<<word_id<<" "<<word<<" "<<freq<<endl;
		if(word_id == 0){
			cerr<<"ERROR: id 0 is reserved for special token NULL, in line: "<<line<<"\n";
			exit(-1);
		}
		else if (word_id >= MAX_VOCAB_SIZE){
   			cerr << "ERROR: TOKEN ID is greater than maximum vocabulary size "<< MAX_VOCAB_SIZE << " in line :\n"<< line <<"\n" ;
   			exit(-1);
   		}	
   		else if (freq < 0){
  			cerr << "ERROR: frequency must be a positive integer, in line :\n"<< line <<"\n";
   			exit(-1);
   		}
   		else if(word_id < volist.size()){
  			cerr << "ERROR: TOKEN ID must be unique for each token, in line :\n"<< line <<"\n";
   			cerr << "TOKEN ID " << word_id << " has already been assigned to: " <<volist[word_id].word << "\n";
   			exit(-1);
   		}
   		else { // line  has valid information
			entry.word = word;
			entry.freq = freq;
			volist.push_back(entry);
			s2i[word] = word_id;
			noUniqueTokens++;
   		}
	}
}


