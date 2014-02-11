
#include "model12.h"

string zsInt2String(int i){
    ostringstream buf;
    buf<<i;
    return buf.str();
}


void model12::train_init1(const char* fn_snt){
  sHander.init(fn_snt);
	sHander.new_start();
	SentPair sent;
	WordIndex i, j, l, m;

	while(sHander.getNextSentence(sent)){
		vector<WordIndex>& es = sent.esent;
		vector<WordIndex>& fs = sent.fsent;
		l = es.size() - 1;
		m = fs.size() - 1;
		double uniform = 1.0/es.size();
		for(j=0;j <= l ;j++){
			count_e[es[j]] = 0;
			//count_jlm[j*G2+l*G1+m] = 0;
			for(i=1;i <= m;i++){
				cal_ef[WordPairIds(es[j],fs[i])].count = 0;
				cal_ef[WordPairIds(es[j],fs[i])].prob = uniform;
				//count_jilm[j*G3+i*G2+l*G1+m] = 0;
				//q_jilm[j*G3+i*G2+l*G1+m] = 0;
			}
		}
		//for(i=1;i <= m;i++)
		//	count_ilm[i*G2+l*G1+m] = 0;
	}

}

void model12::train_init12(const char* fn_snt){
  sHander.init(fn_snt);
	sHander.new_start();
	SentPair sent;
	WordIndex i, j, l, m;

	while(sHander.getNextSentence(sent)){
		vector<WordIndex>& es = sent.esent;
		vector<WordIndex>& fs = sent.fsent;
		l = es.size() - 1;
		m = fs.size() - 1;
		double uniform = 1.0/es.size();
		for(j=0;j <= l ;j++){
			count_e[es[j]] = 0;
			count_jlm[j*G2+l*G1+m] = 0;
			for(i=1;i <= m;i++){
				cal_ef[WordPairIds(es[j],fs[i])].count = 0;
				cal_ef[WordPairIds(es[j],fs[i])].prob = uniform;
				count_jilm[j*G3+i*G2+l*G1+m] = 0;
				q_jilm[j*G3+i*G2+l*G1+m] = 0;
			}
		}
		for(i=1;i <= m;i++)
			count_ilm[i*G2+l*G1+m] = 0;
	}

}

void model12::em_algo1(int noIterations){
	WordIndex i, j, l, m;
	SentPair sent;
	double sum, temp;
	for(int noit=1;noit <= noIterations;noit++){
		cout<<"IBM Model 1 ...EM Algorithm Iteration "<<noit<<"\n";
    //set all the counts to 0
		sHander.new_start();
		cout<<"Clear counts in last iteration."<<"\n";
		while(sHander.getNextSentence(sent)){
			vector<WordIndex>& es = sent.esent;
			vector<WordIndex>& fs = sent.fsent;
			l = es.size() - 1;
			m = fs.size() - 1;
			for(j=0;j <= l ;j++){
				count_e[es[j]] = 0;
				//count_jlm[j*G2+l*G1+m] = 0;
				for(i=1;i <= m;i++){
					cal_ef[WordPairIds(es[j],fs[i])].count = 0;
					//count_jilm[j*G3+i*G2+l*G1+m] = 0;
				}
			}
			//for(i=1;i <= m;i++)
			//	count_ilm[i*G2+l*G1+m] = 0;
		}
    //estimate process
	  sHander.new_start();
		while(sHander.getNextSentence(sent)){
			vector<WordIndex>& es = sent.esent;
			vector<WordIndex>& fs = sent.fsent;
			l = es.size() - 1;
			m = fs.size() - 1;
			for(i=1;i <= m;i++){
				sum = 0;
				for(j=0;j <= l;j++)
					sum += cal_ef[WordPairIds(es[j], fs[i])].prob;
				for(j=0;j <= l;j++){
					temp = cal_ef[WordPairIds(es[j], fs[i])].prob/sum;
					cal_ef[WordPairIds(es[j], fs[i])].count += temp;
					count_e[es[j]] += temp;
					//count_jilm[j*G3+i*G2+l*G1+m] += temp;
					//count_ilm[i*G2+l*G1+m] += temp;
				}
			}
		}
    //maximize process
		sHander.new_start();
		while(sHander.getNextSentence(sent)){
			vector<WordIndex>& es = sent.esent;
			vector<WordIndex>& fs = sent.fsent;
			l = es.size() - 1;
			m = fs.size() - 1;
			for(i=1;i <= m;i++){
				for(j=0;j <= l;j++){
					cal_ef[WordPairIds(es[j], fs[i])].prob = cal_ef[WordPairIds(es[j], fs[i])].count/count_e[es[j]];
					//q_jilm[j*G3+i*G2+l*G1+m] = count_jilm[j*G3+i*G2+l*G1+m]/count_ilm[i*G2+l*G1+m];
				}//end of for j
			}//end of for i
		}//end of while

	}//end of for iteration

}


void model12::print_tfe(const char* fn_tfe){
  cout<<"printing t(f|e) information into file "<<fn_tfe<<endl;
  ofstream of(fn_tfe);
  int cnt = 0;

  hash_map<WordPairIds, CPPair, hashpair, equal_to<WordPairIds> >::iterator pt = cal_ef.begin();
  for(pt=cal_ef.begin();pt != cal_ef.end();pt++){
    of<<(*pt).first.first<<"  "<<(*pt).first.second<<"  "<<(*pt).second.prob<<"\n";
    cnt++;
  }
  cout<<"there are "<<cnt<<" pairs in total."<<endl;

}


void model12::decode_init1(string en, string fr, int N, const char* fn_tfe){
  /******reading t(f|e) probability******/
  ifstream in_tfe(fn_tfe);
  if(!in_tfe){
    cerr<<"Error: cannot open t(f|e) file "<<fn_tfe<<endl;
    exit(1);
  }

  cal_ef.clear();
  cout<<"Reading t(f|e) information from file "<<fn_tfe<<endl;
  string tline;
  int tfe_cnt = 0;
  while(getline(in_tfe, tline)){
    WordIndex en_id, fr_id;
    double pp;
    tfe_cnt++;

    istringstream buffer_tline(tline);
    if(!( (buffer_tline>>en_id)&&(buffer_tline>>fr_id)&&(buffer_tline>>pp) )){
      cerr<<"Error: uncorrect format in line "<<tfe_cnt<<endl;
      exit(1);
    }
    cal_ef[WordPairIds(en_id, fr_id)].prob = pp;
  }

  string en_line, fr_line, temp_str;
  /******reading en test corpus******/
  ifstream in_en(en.c_str());
  if(!in_en){
    cerr<<"Error: cannot open file "<<en<<endl;
    exit(1);
  }
  cout<<"Reading test corpus from file "<<en<<endl;
  while(getline(in_en, en_line)){
    vector<WordIndex> en_temp_sent;
    en_temp_sent.push_back(0);
    istringstream buffer_en(en_line);
    while(buffer_en>>temp_str){
      en_temp_sent.push_back( EList[temp_str] );
    }
    decode_en.push_back(en_temp_sent);
  }

  /******reading fr test corpus******/
  vector<vector<WordIndex> > zero_array;
  decode_frarr.push_back(zero_array);
  for(int i=1;i <= N;i++){
    decode_frarr.push_back(zero_array);

    string fn_file = fr + zsInt2String(i);
    ifstream in_fr(fn_file.c_str());
    if(!in_fr){
      cerr<<"Error: cannot open file "<<fn_file<<endl;
      exit(1);
    }
    cout<<"Reading test corpus from file "<<fn_file<<endl;
    while(getline(in_fr, fr_line)){
      vector<WordIndex> fr_temp_sent;
      fr_temp_sent.push_back(0);
      istringstream buffer_fr(fr_line);
      while(buffer_fr>>temp_str){
        fr_temp_sent.push_back( FList[temp_str] );
      }
      decode_frarr[i].push_back(fr_temp_sent);
    }
  }

}

void model12::decoding1(string en, string fr, int N, vector<vector<fs_logp> >& logp_record){
  logp_record.clear();
  vector<fs_logp> temp_logarr;
  logp_record.push_back(temp_logarr);
  for(int k=1;k <= N;k++)
    logp_record.push_back(temp_logarr);

  ofstream of_debug("model1prob.debug");//output t(tg1|src) probability

  WordIndex i, j, l, m;
  double temp, temp_pp;
  int noline = decode_en.size();
  for(int k=1;k <= N;k++){
    for(int rr=0;rr < noline;rr++){
      vector<WordIndex>& es = decode_en[rr];
      vector<WordIndex>& fs = decode_frarr[k][rr];
      l = es.size() - 1;
      m = fs.size() - 1;
      double sum_logp = -m*log(l+1);
      for(i=1;i <= m;i++){
        temp = 0;
        for(j=0;j <= l;j++){
          if( cal_ef.find(WordPairIds(es[j], fs[i])) == cal_ef.end() )
            temp_pp = 0.1e-10;
          else
            temp_pp = cal_ef[WordPairIds(es[j], fs[i])].prob;

          if(temp_pp > temp){
            temp = temp_pp;
          }
        }
        sum_logp += log(temp);
      }

      of_debug<<sum_logp<<"\n";//output log t(tg1|src)

      logp_record[k].push_back( fs_logp(k, sum_logp) );
    }
  }

}


void model12::Decoder1(string en, string fr, int N, const char* fn_tfe, vector<vector<fs_logp> >& logp_record){

  decode_init1(en, fr, N, fn_tfe);
  decoding1(en, fr, N, logp_record);

}



void model12::em_algo2(int noIterations){
	WordIndex i, j, l, m;
	SentPair sent;
	double sum, temp;
	for(int noit=1;noit <= noIterations;noit++){
		cout<<"IBM Model 2 ...EM Algorithm Iteration "<<noit<<"\n";

		sHander.new_start();
		cout<<"Clear counts in last iteration."<<"\n";
		while(sHander.getNextSentence(sent)){
			vector<WordIndex>& es = sent.esent;
			vector<WordIndex>& fs = sent.fsent;
			l = es.size() - 1;
			m = fs.size() - 1;
			for(j=0;j <= l ;j++){
				count_e[es[j]] = 0;
				count_jlm[j*G2+l*G1+m] = 0;
				for(i=1;i <= m;i++){
					cal_ef[WordPairIds(es[j],fs[i])].count = 0;
					count_jilm[j*G3+i*G2+l*G1+m] = 0;
				}
			}
			for(i=1;i <= m;i++)
				count_ilm[i*G2+l*G1+m] = 0;
		}

	    sHander.new_start();
		while(sHander.getNextSentence(sent)){
			vector<WordIndex>& es = sent.esent;
			vector<WordIndex>& fs = sent.fsent;
			l = es.size() - 1;
			m = fs.size() - 1;
			for(i=1;i <= m;i++){
				sum = 0;
				for(j=0;j <= l;j++)
					sum += q_jilm[j*G3+i*G2+l*G1+m]*cal_ef[WordPairIds(es[j], fs[i])].prob;
				for(j=0;j <= l;j++){
					temp = q_jilm[j*G3+i*G2+l*G1+m]*cal_ef[WordPairIds(es[j], fs[i])].prob/sum;
					cal_ef[WordPairIds(es[j], fs[i])].count += temp;
					count_e[es[j]] += temp;
					count_jilm[j*G3+i*G2+l*G1+m] += temp;
					count_ilm[i*G2+l*G1+m] += temp;
				}
			}
		}
		sHander.new_start();
		while(sHander.getNextSentence(sent)){
			vector<WordIndex>& es = sent.esent;
			vector<WordIndex>& fs = sent.fsent;
			l = es.size() - 1;
			m = fs.size() - 1;
			for(i=1;i <= m;i++){
				for(j=0;j <= l;j++){
					cal_ef[WordPairIds(es[j], fs[i])].prob = cal_ef[WordPairIds(es[j], fs[i])].count/count_e[es[j]];
					q_jilm[j*G3+i*G2+l*G1+m] = count_jilm[j*G3+i*G2+l*G1+m]/count_ilm[i*G2+l*G1+m];
				}
			}
		}
	}

}


void model12::print_align(ofstream& of)
{
	WordIndex i, j, l, m;
	SentPair sent;
	double temp, temp_qt;
	PositionIndex temp_index;
	sHander.new_start();
	while(sHander.getNextSentence(sent)){
		vector<PositionIndex> al_ij;
		al_ij.clear();
		al_ij.push_back(0);
		vector<WordIndex>& es = sent.esent;
		vector<WordIndex>& fs = sent.fsent;
		l = es.size() - 1;
		m = fs.size() - 1;
		for(i=1;i <= m;i++){
			temp = 0;
			for(j=0;j <= l;j++){
				temp_qt = cal_ef[WordPairIds(es[j], fs[i])].prob * q_jilm[j*G3+i*G2+l*G1+m];
				if(temp_qt > temp){
					temp = temp_qt;
					temp_index = j;
				}
			}
			al_ij.push_back(temp_index);
		}

		of<<"#sentence pair ("<<sent.sentenceNo<<") f sentence length "<<m<<", e sentence length "<<l<<"\n";
		for(i=1;i <= m;i++)
			of<<FList[fs[i]]<<" ";
		of<<"\n";
		for(j=0;j <= l;j++){
			of<<EList[es[j]]<<" ({ ";
			for(i=1;i <= m;i++){
				if(al_ij[i] == j)
					of<<i<<" ";
			}
			of<<"}) ";
		}
		of<<endl;
	}
}

void model12::cal_logp(int no, vector<fs_logp>& fe_logp){
	WordIndex i, j, l, m;
	SentPair sent;
	double temp, temp_qt, sum_logp;
	PositionIndex temp_index;
	sHander.new_start();
	while(sHander.getNextSentence(sent)){
		sum_logp = 0;
		vector<WordIndex>& es = sent.esent;
		vector<WordIndex>& fs = sent.fsent;
		l = es.size() - 1;
		m = fs.size() - 1;
		for(i=1;i <= m;i++){
			temp = 0;
			for(j=0;j <= l;j++){
				temp_qt = cal_ef[WordPairIds(es[j], fs[i])].prob;
				if(temp_qt > temp){
					temp = temp_qt;
					temp_index = j;
				}
			}
			sum_logp += log(temp);
		}
		fe_logp.push_back(fs_logp(no, sum_logp));
	}
}

