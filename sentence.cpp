
#include "sentence.h"

SentenceHandle::SentenceHandle(const char* fn){
	filename = fn;
	p_inputFile = new ifstream(filename);
	if(!(*p_inputFile)){
		cerr<<"ERROR: can not open the file: "<<filename<<endl;
		exit(1);
	}
	currentSentence = 0;
	noSentInBuffer = 0;
	pair_no = 0;
	totalPair = 0;
	sent_buffer.clear();
	
	cout<<"Calculating vocabulary frequencies from corpus "<<filename<<endl;
	SentPair s;
	while(getNextSentence(s))
		totalPair++;
	currentSentence = 0;
}

void SentenceHandle::new_start(){
	currentSentence = 0;
	noSentInBuffer = 0;
	pair_no = 0;
	totalPair = 0;
	sent_buffer.clear();

	delete p_inputFile;
	p_inputFile = new ifstream(filename);
	if(!(*p_inputFile)){
		cerr<<"ERROR: cannot open file "<<filename<<endl;
		exit(0);
	}
}


bool SentenceHandle::getNextSentence(SentPair& sent){
	SentPair sent_temp;
	if(currentSentence >= noSentInBuffer){
	//	noSentInBuffer = 0;
	//	currentSentence = 0;
	//	sent_buffer.clear();
	
		if(currentSentence == 0)
			cout<<"reading more sentence pair into memory......"<<endl;
		else 
			cout<<"already readed into the memory......"<<endl;

		while((noSentInBuffer <= TRAIN_BUFFER_SIZE)&&(readNextSentence(sent_temp))){
			sent_buffer.push_back(sent_temp);
			noSentInBuffer++;
		}
	}
	if(currentSentence >= noSentInBuffer)
		return false;
	sent = sent_buffer[currentSentence++];
	return true;
}

bool SentenceHandle::readNextSentence(SentPair& sent){
	string line;
	bool fail(false);
	sent.clear();

	if(getline(*p_inputFile, line)){
		istringstream word_buffer(line);
		word_buffer>>sent.noOcc;
	}
	else
		fail = true;
	if(getline(*p_inputFile, line)){
		istringstream word_buffer(line);
		WordIndex w;
		sent.esent.push_back(0);
		while(word_buffer>>w)
			sent.esent.push_back(w);
	}
	else
		fail = true;
	if(getline(*p_inputFile, line)){
		istringstream word_buffer(line);
		WordIndex w;
		sent.fsent.push_back(0);
		while(word_buffer>>w)
			sent.fsent.push_back(w);
	}
	else
		fail = true;

	if((sent.esent.size() > MAX_SENTENCE_LENGTH)||(sent.esent.size() > MAX_SENTENCE_LENGTH)){
		cerr<<"Sentence length is too large. Sentence number:"<<noSentInBuffer<<endl;
		exit(1);
	}

	if(fail == true){
		sent.esent.clear();
		sent.fsent.clear();
		sent.sentenceNo = 0;
		sent.noOcc = 0;
		return false;
	}

	sent.sentenceNo = ++pair_no;
	
	return true;
}



