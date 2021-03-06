
#include "rankmodel.h"

string zsInt2String(int i){
    ostringstream buf;
    buf<<i;
    return buf.str();
}

string zsDouble2String(double x){
  ostringstream buf;
  buf << x;
  return buf.str();
}

int min2(int t1, int t2){
	if(t1 <= t2)
		return t1;
	else
		return t2;
}

int min3(int t1, int t2, int t3){
	return min2(min2(t1, t2), t3);
}

void lsdalignment(const vector<string>& f1, const vector<string>& f2, vector<string>& ans){
	//cout<<"execute ldsalignment"<<endl;
  const unsigned int ML = MAX_SENTENCE_LENGTH;
	int lds_matrix[ML][ML];
	int row = f1.size();
	int col = f2.size();
	int i, j;

	for(i=0;i <= row;i++)
		lds_matrix[i][0] = i;
	for(j=0;j <= col;j++)
		lds_matrix[0][j] = j;
	for(i=1;i <= row;i++){
		for(j=1;j <= col;j++){
			if(f1[i-1] == f2[j-1])
				lds_matrix[i][j] = lds_matrix[i-1][j-1];
			else
				lds_matrix[i][j] = min3(lds_matrix[i-1][j-1]+1, lds_matrix[i][j-1]+1, lds_matrix[i-1][j]+1);
		}
	}

	vector<string>::iterator it;
	string temp_s;
	i = row;
	j = col;
	while((i>=1)&&(j>=1)){
		if(f1[i-1] == f2[j-1]){
			it = ans.begin();
			temp_s = f1[i-1] + " " + f2[j-1];
			ans.insert(it, temp_s);
			i--;
			j--;
		}
		else{
			if((lds_matrix[i][j-1]+1) == lds_matrix[i][j]){
				it = ans.begin();
				temp_s = "NULL " + f2[j-1];
				ans.insert(it, temp_s);
				j--;
			}
			else if((lds_matrix[i-1][j]+1) == lds_matrix[i][j]){
				it = ans.begin();
				temp_s = f1[i-1] + " NULL";
				ans.insert(it, temp_s);
				i--;
			}
			else if((lds_matrix[i-1][j-1]+1) == lds_matrix[i][j]){
				it = ans.begin();
				temp_s = f1[i-1] + " " + f2[j-1];
				ans.insert(it, temp_s);
				i--;
				j--;
			}
			else
				cerr<<"something wrong with lds_matrix["<<i<<"]["<<j<<"]\n";
		}
	}

	if((i==0) && (j==0)){}
	else if ((i==0) && (j!=0)){
		for(;j>=1;j--){
			it = ans.begin();
			temp_s = "NULL " + f2[j-1];
			ans.insert(it, temp_s);
		}
	}
	else if ((i!=0) && (j==0)){
		for(;i>=1;i--){
			it = ans.begin();
			temp_s = f1[i-1] + " NULL";
			ans.insert(it, temp_s);
		}
	}
	else
		cerr<<"something wrong in if row==0 && col==0"<<endl;

}


void lsda_pht(const vector<string>& f1, const vector<string>& f2, vector<string>& ans){
	//cout<<"execute ldsalignment"<<endl;
  const unsigned int ML = MAX_SENTENCE_LENGTH;
	int lds_matrix[ML][ML];
	int row = f1.size();
	int col = f2.size();
	int i, j;

	for(i=0;i <= row;i++)
		lds_matrix[i][0] = i;
	for(j=0;j <= col;j++)
		lds_matrix[0][j] = j;
	for(i=1;i <= row;i++){
		for(j=1;j <= col;j++){
			if(f1[i-1] == f2[j-1])
				lds_matrix[i][j] = lds_matrix[i-1][j-1];
			else
				lds_matrix[i][j] = min3(lds_matrix[i-1][j-1]+1, lds_matrix[i][j-1]+1, lds_matrix[i-1][j]+1);
		}
	}

	vector<string>::iterator it;
	string temp_s;
	i = row;
	j = col;
	while((i>=1)&&(j>=1)){
		if(f1[i-1] == f2[j-1]){
			it = ans.begin();
			temp_s = f1[i-1] + " " + f2[j-1];
			ans.insert(it, temp_s);
			i--;
			j--;
		}
		else{
			if((lds_matrix[i][j-1]+1) == lds_matrix[i][j]){
				it = ans.begin();
				temp_s = "NULL " + f2[j-1];
				//ans.insert(it, temp_s);
				j--;
			}
			else if((lds_matrix[i-1][j]+1) == lds_matrix[i][j]){
				it = ans.begin();
				temp_s = f1[i-1] + " NULL";
				ans.insert(it, temp_s);
				i--;
			}
			else if((lds_matrix[i-1][j-1]+1) == lds_matrix[i][j]){
				it = ans.begin();
				temp_s = f1[i-1] + " " + f2[j-1];
				ans.insert(it, temp_s);
				i--;
				j--;
			}
			else
				cerr<<"something wrong with lds_matrix["<<i<<"]["<<j<<"]\n";
		}
	}

	if((i==0) && (j==0)){}
	else if ((i==0) && (j!=0)){
		for(;j>=1;j--){
			it = ans.begin();
			temp_s = "NULL " + f2[j-1];
			//ans.insert(it, temp_s);
		}
	}
	else if ((i!=0) && (j==0)){
		for(;i>=1;i--){
			it = ans.begin();
			temp_s = f1[i-1] + " NULL";
			ans.insert(it, temp_s);
		}
	}
	else
		cerr<<"something wrong in if row==0 && col==0"<<endl;

}


void RankModel::readcorpus(const char* in_file){
	if (rankcorpus.size() != 0){
		rankcorpus.clear();
		cout<<"clear old data in rankcorpus. rankcorpus.size() = "<<rankcorpus.size()<<endl;
	}

	ifstream in_corpus(in_file);
	if(!in_corpus)
		cerr<<"cannot open file"<<in_file<<endl;
	cout<<"......reading corpus from file "<<in_file<<"......"<<endl;
	string no_line, en_line, ff_line;
	while(getline(in_corpus, no_line) && getline(in_corpus, en_line) && getline(in_corpus, ff_line)){
		RankSent temp_rank;
		WordIndex i, x, y;

		istringstream buffer_no(no_line);
		buffer_no>>temp_rank.noSent;

		istringstream buffer_en(en_line);
		temp_rank.esent.push_back(0);
		while(buffer_en>>i)
			temp_rank.esent.push_back(i);

		istringstream buffer_ff(ff_line);
		temp_rank.ffsent.push_back(FPair(0, 0));
		while((buffer_ff>>x) && (buffer_ff>>y))
			temp_rank.ffsent.push_back(FPair(x, y));

		rankcorpus.push_back(temp_rank);
	}
	cout<<"......corpus is already contained in memory.........."<<endl;
}

void RankModel::train_init1(){
	WordIndex i, j, l, m;
	cout<<"..........RankModel Initialization!.........."<<endl;

	for(unsigned int k=0;k < rankcorpus.size();k++){
		RankSent& temp_sent = rankcorpus[k];
		vector<WordIndex>& es = temp_sent.esent;
		vector<FPair>& ffs = temp_sent.ffsent;
		l = es.size() - 1;
		m = ffs.size() - 1;
		double uniform = 1.0/es.size();
		for(j=0;j <= l;j++){
			count_e[es[j]] = 0;
			for(i=1;i <= m;i++){
				info_fe[WordPairIds(ffs[i].ft_id, es[j])].count = 0;
				info_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].count = 0;
				info_fe[WordPairIds(ffs[i].ft_id, es[j])].prob = uniform;
				info_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob = uniform;
			}
		}
	}
}

void RankModel::train_init2(){
	WordIndex i, j, l, m;
	cout<<"..........RankModel Initialization!.........."<<endl;

	for(unsigned int k=0;k < rankcorpus.size();k++){
		RankSent& temp_sent = rankcorpus[k];
		vector<WordIndex>& es = temp_sent.esent;
		vector<FPair>& ffs = temp_sent.ffsent;
		l = es.size() - 1;
		m = ffs.size() - 1;
		double uniform = 1.0/es.size();
		for(j=0;j <= l;j++){
			count_e[es[j]] = 0;
			for(i=1;i <= m;i++){
				t_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].count = 0;
				t_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob = uniform;
			}
		}
	}
}

void RankModel::em_algo1(int noIterations){
	WordIndex i, j, l, m;
	double sum1, deta1, sum2, deta2;
	cout<<"RankModel em algorithm 1, iteration number "<<noIterations<<endl;
	for(int it=1;it <= 2*noIterations;it++){
		cout<<"............iteration "<<it/2<<"..............."<<endl;
		//set all counts to zero
		bool flag = ((it%2) == 0);
		for(unsigned int k=0;k < rankcorpus.size();k++){
			RankSent& temp_sent = rankcorpus[k];
			vector<WordIndex>& es = temp_sent.esent;
			vector<FPair>& ffs = temp_sent.ffsent;
			l = es.size() - 1;
			m = ffs.size() - 1;
			for(j=0;j <= l;j++){
				count_e[es[j]] = 0;
				for(i=1;i <= m;i++){
					info_fe[WordPairIds(ffs[i].ft_id, es[j])].count = 0;
					info_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].count = 0;
				}
			}
		}

		//E step
		for(unsigned int k=0;k < rankcorpus.size();k++){
			RankSent& temp_sent = rankcorpus[k];
			vector<WordIndex>& es = temp_sent.esent;
			vector<FPair>& ffs = temp_sent.ffsent;
			l = es.size() - 1;
			m = ffs.size() - 1;
			for(i=1;i <= m;i++){
				sum1 = 0;
				sum2 = 0;
				for(j=0;j <= l;j++){
					if(flag)
						sum1 += info_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob;
					else
						sum2 += info_fe[WordPairIds(ffs[i].ft_id, es[j])].prob;
				}
				for(j=0;j <= l;j++){
					if(flag){
						deta1 = info_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob / sum1;
						info_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].count += deta1;
						info_fe[WordPairIds(ffs[i].ft_id, es[j])].count += deta1;
					}
					else{
						deta2 = info_fe[WordPairIds(ffs[i].ft_id, es[j])].prob / sum2;
						info_fe[WordPairIds(ffs[i].ft_id, es[j])].count += deta2;
						count_e[es[j]] += deta2;
					}
				}
			}
		}//end of E step

		//M step
		for(unsigned int k=0;k < rankcorpus.size();k++){
			RankSent& temp_sent = rankcorpus[k];
			vector<WordIndex>& es = temp_sent.esent;
			vector<FPair>& ffs = temp_sent.ffsent;
			l = es.size() - 1;
			m = ffs.size() - 1;
			for(j=0;j <= l;j++){
				for(i=1;i <= m;i++){
					if(flag)
						info_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob = info_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].count / info_fe[WordPairIds(ffs[i].ft_id, es[j])].count;
					else
						info_fe[WordPairIds(ffs[i].ft_id, es[j])].prob = info_fe[WordPairIds(ffs[i].ft_id, es[j])].count / count_e[es[j]];
				}
			}
		}//end of M step

	}//end of for iterations

}//end of em_algo

void RankModel::em_algo2(int noIterations){
	WordIndex i, j, l, m;
	double sum, deta;
	cout<<"..........RankModel em algorithm 2, iteration number "<<noIterations<<".........."<<endl;
	for(int it=1;it <= noIterations;it++){
		cout<<"............iteration "<<it<<"..............."<<endl;
		//set all counts to zero
		for(unsigned int k=0;k < rankcorpus.size();k++){
			RankSent& temp_sent = rankcorpus[k];
			vector<WordIndex>& es = temp_sent.esent;
			vector<FPair>& ffs = temp_sent.ffsent;
			l = es.size() - 1;
			m = ffs.size() - 1;
			for(j=0;j <= l;j++){
				count_e[es[j]] = 0;
				for(i=1;i <= m;i++){
					t_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].count = 0;
				}
			}
		}

		//E step
		for(unsigned int k=0;k < rankcorpus.size();k++){
			RankSent& temp_sent = rankcorpus[k];
			vector<WordIndex>& es = temp_sent.esent;
			vector<FPair>& ffs = temp_sent.ffsent;
			l = es.size() - 1;
			m = ffs.size() - 1;
			for(i=1;i <= m;i++){
				sum = 0;
				for(j=0;j <= l;j++){
					sum += t_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob;
				}
				for(j=0;j <= l;j++){
						deta = t_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob / sum;
						t_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].count += deta;
						count_e[es[j]] += deta;
				}
			}
		}

		//M step
		for(unsigned int k=0;k < rankcorpus.size();k++){
			RankSent& temp_sent = rankcorpus[k];
			vector<WordIndex>& es = temp_sent.esent;
			vector<FPair>& ffs = temp_sent.ffsent;
			l = es.size() - 1;
			m = ffs.size() - 1;
			for(j=0;j <= l;j++){
				for(i=1;i <= m;i++){
						t_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob = t_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].count / count_e[es[j]];
				}
			}
		}

    //calculate log-likelihood
    double logp_corpus = 1;
		for(unsigned int k=0;k < rankcorpus.size();k++){
			RankSent& temp_sent = rankcorpus[k];
			vector<WordIndex>& es = temp_sent.esent;
			vector<FPair>& ffs = temp_sent.ffsent;
			l = es.size() - 1;
			m = ffs.size() - 1;
      double prob_sent = 1;
      double ptmp_max = 0;
      for(i=1;i <= m;i++){
        ptmp_max = 0;
				for(j=0;j <= l;j++){
					if(t_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob > ptmp_max)
            ptmp_max = t_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob;
				}
        if(ptmp_max == 0){
          cerr<<"ERROR in ptmp_max"<<endl;
          exit(1);
        }
        prob_sent *= ptmp_max;
			}
      logp_corpus += log(prob_sent);
		}
    cout<<"====>Iteration "<<it<<" logp_corpus : "<<logp_corpus<<endl;

	}
}




void RankModel::decode_init(string en_name, string fr_name, int N, vector<vector<fs_logp> >& logp_record){
  cout<<"......decode Initialization......"<<endl;
  ifstream in_en(en_name.c_str());
  if(!in_en){
    cerr<<"ERROR: cannot open file "<<en_name<<endl;
    exit(1);
  }
  string en_line, fr_line, temp_string;

  cout<<"......reading "<<en_name<<" test corpus......"<<endl;
  //reading en corpus
  while(getline(in_en, en_line)){
    vector<WordIndex> en_temp_sent;
    en_temp_sent.push_back(0);
    istringstream buffer_en(en_line);
    while(buffer_en>>temp_string){
      en_temp_sent.push_back( EList[temp_string] );
    }
    decode_en.push_back(en_temp_sent);
  }

  vector<vector<string> > zero_array;
  decode_frarr.push_back(zero_array);
  for(int i=1;i <= N;i++){
    decode_frarr.push_back(zero_array);

    string fn_file = fr_name + zsInt2String(i);
    cout<<"......reading "<<fn_file<<" test corpus......"<<endl;
    ifstream in_fr(fn_file.c_str());
    if(!in_fr){
      cerr<<"ERROR: cannot open file "<<fn_file<<endl;
      exit(1);
    }

    //reading fr corpus
    vector<vector<string> >& rd_fr = decode_frarr[i];
    while(getline(in_fr, fr_line)){
      vector<string> fr_temp_sent;
      istringstream buffer_fr(fr_line);
      while(buffer_fr>>temp_string){
        fr_temp_sent.push_back(temp_string);
      }
      rd_fr.push_back(fr_temp_sent);
    }
  }

}

void RankModel::decoding(string en_name, string fr_name, int N, vector<vector<fs_logp> >& logp_record){
  cout<<"......RankModel Decoding......"<<endl;
  int noline = decode_en.size();
  double temp, temp_pp;
  int temp_index;

  logp_record.clear();
  if(logp_record.size() != 0){
    cerr<<"logp_array size error. "<<endl;
    exit(1);
  }
  vector<fs_logp> zero_logpa;
  logp_record.push_back(zero_logpa);
  for(int i=1;i <= N;i++)
    logp_record.push_back(zero_logpa);

//  ofstream of_debug1("sentprob.debug");// output debug 1 src#tg1#tg2#p(tg1,tg2|src)
//  ofstream of_debug2("rankprob.debug");// output debug 2 p(tg1 | src)

  for(int i=1;i <= N;i++){
    bool flag_1st = true;
    cout<<"handling "<<fr_name<<i<<" file"<<endl;
    vector<vector<string> >& f_corpus = decode_frarr[i];
    for(int j=1;j <= N;j++){
      if(i != j){

//        string fn_lsda = fr_name + zsInt2String(i) + "_" + zsInt2String(j) + ".comp";
//        ofstream of_lsda(fn_lsda.c_str());

        cout<<"handling "<<fr_name<<i<<"_"<<j<<" part"<<endl;
        vector<vector<string> >& ft_corpus = decode_frarr[j];
        if((f_corpus.size() != noline)||(ft_corpus.size() != noline)){
            cerr<<"error in fr corpus length "<<i<<" "<<j<<endl;
            cerr<<noline<<endl;
            cerr<<f_corpus.size()<<" "<<ft_corpus.size()<<endl;
            exit(1);
        }
        cout<<"$$$flag_1st : "<<flag_1st<<endl;
        for(int k=0;k < noline;k++){
          vector<WordIndex>& es = decode_en[k];

          vector<string>& f_temp_sent = f_corpus[k];
          vector<string>& ft_temp_sent = ft_corpus[k];
          vector<string> lsda_temp_sent;
          //cout<<"doing alignment line "<<k+1<<endl;
          lsdalignment(f_temp_sent, ft_temp_sent, lsda_temp_sent);

/*output debug 1 src ||| tg1 ||| tg2  */
//          for(vector<WordIndex>::iterator dt=es.begin();dt != es.end();dt++)
//              of_debug1<<EList[*dt]<<" ";
//          of_debug1<<" ||| ";
//          for(vector<string>::iterator dt=f_temp_sent.begin();dt != f_temp_sent.end();dt++)
//              of_debug1<<*dt<<" ";
//          of_debug1<<" ||| ";
//          for(vector<string>::iterator dt=ft_temp_sent.begin();dt != ft_temp_sent.end();dt++)
//              of_debug1<<*dt<<" ";
//          of_debug1<<" ||| ";
//          for(int rr=0;rr < lsda_temp_sent.size();rr++)
//              of_lsda<<lsda_temp_sent[rr]<<"  ";
//          of_lsda<<"\n";

          double sent_logp = 1;
          for(int rr=0;rr < lsda_temp_sent.size();rr++){
            istringstream buffer_ffid(lsda_temp_sent[rr]);
            string fr_str, ft_str;
            if( !((buffer_ffid>>fr_str)&&(buffer_ffid>>ft_str)) ){
              cerr<<"ERROR: decoding "<<i<<" "<<j<<" "<<k<<" "<<rr<<" part"<<endl;
              exit(1);
            }
            WordIndex fr_id = FList[fr_str];
            WordIndex ft_id = FList[ft_str];

//            of_lsda<<fr_id<<" "<<ft_id<<"  ";

            temp = 0;
            for(int cc=0;cc < es.size();cc++){
              if(t_ffe.find(FFEPair(fr_id, ft_id, es[cc])) == t_ffe.end())
         				temp_pp = 0.1e-10;
         			else
  	    				temp_pp = t_ffe[FFEPair(fr_id, ft_id, es[cc])].prob;
  	    			if(temp_pp > temp){
  	    				temp = temp_pp;
                temp_index = cc;
  	    			}
  	    		}
  	     		sent_logp *= temp;
//            of_lsda<<es[temp_index]<<"  "<<sent_logp<<" | ";

  	    	}

//          of_debug1<<log(sent_logp)<<"\n";//output debug 1 log p(tg1,tg2|src)
//          of_lsda<<"\n";

          if(flag_1st)
            logp_record[i].push_back( fs_logp(i, sent_logp) );
          else
            logp_record[i][k].logp += sent_logp;
        }
        flag_1st = false;

      }//end of if
    }

/* output debug 2 log p(tg1|src) */
//    for(int qq=0;qq < noline;qq++)
//        of_debug2<<log( logp_record[i][qq].logp )<<"\n";

  }
  cout<<"......Decoding Successful......"<<endl;
}

void RankModel::read_tffe(const char* fn_tffe){

  /* reading t(f, f'|e) from fn_tffe file */
  ifstream in_tf(fn_tffe);
  if(!in_tf){
    cerr<<"error: cannot open file "<<fn_tffe<<endl;
    exit(1);
  }
  t_ffe.clear();
  cout<<"......Reading t(f, f'|e) pair from file "<<fn_tffe<<endl;
  WordIndex f_id, ft_id, e_id;
  double temp_logp;
  string temp_line;
  while(getline(in_tf, temp_line)){
    istringstream buffer_line(temp_line);
    if(!((buffer_line>>f_id) && (buffer_line>>ft_id) && (buffer_line>>e_id) && (buffer_line>>temp_logp)))
      cerr<<"ERROR in t(f, f'|e) pair"<<endl;
    t_ffe[ FFEPair(f_id, ft_id, e_id) ].prob = temp_logp;
  }

}


void RankModel::Decoder(string en, string fr, int N, vector<vector<fs_logp> >& logp_record, const char* fn_tffe){
//  ifstream in_tf(fn_tffe);
//  if(!in_tf){
//      cerr<<"error: cannot open file "<<fn_tffe<<endl;
//      exit(1);
//  }
//  t_ffe.clear();
//  cout<<"......reading t(f, f'|e) pair from file "<<fn_tffe<<endl;
//  wordindex f_id, ft_id, e_id;
//  double temp_logp;
//  string temp_line;
//  while(getline(in_tf, temp_line)){
//      istringstream buffer_line(temp_line);
//      if(!((buffer_line>>f_id) && (buffer_line>>ft_id) && (buffer_line>>e_id) && (buffer_line>>temp_logp)))
//          cerr<<"error in t(f, f'|e) pair"<<endl;
//      t_ffe[ ffepair(f_id, ft_id, e_id) ].prob = temp_logp;
//  }
  read_tffe(fn_tffe);
  decode_init(en, fr, N, logp_record);
  decoding(en, fr, N, logp_record);
}

void split(vector<string>& pht_vec, const string& tmp_line, string pattern){
  int pos_s = 0;
  int pos_e = 0;
  int length = tmp_line.size();
  while(pos_e < tmp_line.size()-3){
    pos_e = tmp_line.find(pattern, pos_s);
    string tmp_str = tmp_line.substr(pos_s, pos_e-pos_s);
    pht_vec.push_back(tmp_str);
    pos_s = pos_e + pattern.size();
  }
}

string extrac_head(const string& tmp_line, string pattern){
  int pos_s = 0;
  int pos_e = tmp_line.find(pattern, pos_s);
  return tmp_line.substr(pos_s, pos_e-pos_s);
}

void RankModel::phrasetable_m( map<string, vector<vector<string> > >& pht_map, const char* fn_tffe, const char* fn_pht, const char* fn_npht){
  read_tffe(fn_tffe);

  cout<<"reading phrase-table file : "<<fn_pht<<endl;
  ifstream in_pht(fn_pht);
  ofstream of_npht(fn_npht);
  string pht_line, hstr_cur("$$$^_^$$$");
  while(true){
    bool if_getl = getline( in_pht, pht_line);
    string hstr = extrac_head(pht_line, string(" |||") );
    if (hstr_cur == string("$$$^_^$$$") )
      hstr_cur = hstr;
    vector<string> pht_line_vec;
    split(pht_line_vec, pht_line, string("|||") );
    if ((hstr_cur == hstr) && if_getl){
      //same hstr
      pht_map[hstr].push_back(pht_line_vec);
    }
    else{
      //different hstr, decode algorithm starts from here
      int NT = pht_map[hstr_cur].size();
      cout<<"Manipulating "<<hstr_cur<<"    size : "<<NT<<endl;

      string temp_str;
      //extract f phrase group
      cout<<"extract f phrase group"<<endl;
      vector<vector<string> > pht_ff_group;
      for(int i=0;i < NT;i++){
        istringstream buffer_ff(pht_map[hstr_cur][i][1]);
        vector<string> temp_vec;
        while(buffer_ff>>temp_str){
          temp_vec.push_back(temp_str);
        }
        pht_ff_group.push_back(temp_vec);
      }
      //extract e phrase group
      cout<<"extract e phrase group"<<endl;
      vector<WordIndex> es;
      es.push_back(0);
      istringstream buffer_en(hstr_cur);
      while(buffer_en>>temp_str){
        es.push_back(EList[temp_str]);
      }

      for(int i=0;i < NT;i++){
        cout<<"handling hstr:"<<hstr_cur<<" line:"<<i+1;
        vector<string>& f_temp_sent = pht_ff_group[i];
        double group_prob = 0;
        for(int j=0;j < NT;j++){
          if (i!= j){
            //cout<<"dealing with ("<<i+1<<","<<j+1<<")";
            vector<string>& ft_temp_sent = pht_ff_group[j];
            vector<string> lsda_temp_sent;
            lsdalignment(f_temp_sent, ft_temp_sent, lsda_temp_sent);

            double sent_prob = 1;
            for(int rr=0;rr < lsda_temp_sent.size();rr++){
              istringstream buffer_ffid(lsda_temp_sent[rr]);
              string fr_str, ft_str;
              if( !((buffer_ffid>>fr_str)&&(buffer_ffid>>ft_str)) ){
                cerr<<"ERROR: decoding "<<i<<" "<<j<<" "<<hstr_cur<<" "<<rr<<" part"<<endl;
                exit(1);
              }
              WordIndex fr_id = FList[fr_str];
              WordIndex ft_id = FList[ft_str];

              double temp = 0, temp_pp;
              for(int cc=0;cc < es.size();cc++){
                if(t_ffe.find(FFEPair(fr_id, ft_id, es[cc])) == t_ffe.end())
           				temp_pp = 0.1e-10;
           			else
    	    				temp_pp = t_ffe[FFEPair(fr_id, ft_id, es[cc])].prob;
    	    			if(temp_pp > temp){
    	    				temp = temp_pp;
    	    			}
    	    		}
    	     		sent_prob *= temp;
    	    	}
            group_prob += sent_prob;
            //cout<<" prob: "<<sent_prob<<endl;
          }//end of if
        }

        //output the result
        //pht_map[hstr_cur][i][2] += zsDouble2String(group_prob) + " ";
        cout<<" prob:"<<group_prob<<endl;
        vector<string>& opv = pht_map[hstr_cur][i];
        for(int kk=0;kk < opv.size();kk++){
          if (kk == 2){
            of_npht<<opv[2]<<group_prob<<" |||";
          }
          else{
            of_npht<<opv[kk]<<"|||";
          }
        }
        of_npht<<endl;

      }

      //decode algorithm end, ending process
      pht_map.clear();
      if (if_getl){
        hstr_cur = hstr;
        if(pht_map.find(hstr) != pht_map.end()){
          cerr<<"ERROR: hstr "<<hstr<<"  already in the pht_map "<<endl;
          exit(1);
        }
        pht_map[hstr].push_back(pht_line_vec);
      }

    }//end of else

    if (!if_getl)
      break;
  }//end of while

}


void RankModel::phrasetable_learngiza( map<string, vector<vector<string> > >& pht_map, const char* fn_tffe, const char* fn_pht, const char* fn_npht){
  read_tffe(fn_tffe);

  cout<<"reading phrase-table file : "<<fn_pht<<endl;
  ifstream in_pht(fn_pht);
  ofstream of_npht(fn_npht);
  string pht_line, hstr_cur("$$$^_^$$$");
  int cnt_single = 0;
  int cnt_lines = 0;
  while(true){
    bool if_getl = getline( in_pht, pht_line);
    if (if_getl){
      cnt_lines++;
    }
    string hstr = extrac_head(pht_line, string(" |||") );
    if (hstr_cur == string("$$$^_^$$$") )
      hstr_cur = hstr;
    vector<string> pht_line_vec;
    split(pht_line_vec, pht_line, string("|||") );
    if ((hstr_cur == hstr) && if_getl){
      //same hstr
      pht_map[hstr].push_back(pht_line_vec);
    }
    else{
      //different hstr, decode algorithm starts from here
      int NT = pht_map[hstr_cur].size();
      cout<<"<=(@-@)=>"<<endl;
      cout<<"=>Manipulating "<<hstr_cur<<"    size : "<<NT<<endl;
      if (NT == 1){
        cnt_single++;
      }

      string temp_str;
      //extract alignment information
      cout<<"extract alignment information"<<endl;
      vector<map<int, vector<int> > > pht_alfe_group;
      for(int i=0;i < NT;i++){
        istringstream buffer_al(pht_map[hstr_cur][i][3]);
        map<int, vector<int> > temp_map;
        while(buffer_al>>temp_str){
          int idstr_s = 0;
          int idstr_e = temp_str.find(string("-"), idstr_s);
          int ale = atoi( temp_str.substr(idstr_s, idstr_e - idstr_s).c_str() );
          idstr_s = idstr_e + 1;
          idstr_e = temp_str.length();
          int alf = atoi( temp_str.substr(idstr_s, idstr_e - idstr_s).c_str() );
          temp_map[alf].push_back(ale);

          cout<<ale<<"-"<<alf<<" ";
        }
        cout<<endl;
        pht_alfe_group.push_back(temp_map);
      }

      //extract f phrase group
      cout<<"extract f phrase group"<<endl;
      vector<vector<string> > pht_ff_group;
      for(int i=0;i < NT;i++){
        istringstream buffer_ff(pht_map[hstr_cur][i][1]);
        vector<string> temp_vec;
        while(buffer_ff>>temp_str){
          temp_vec.push_back(temp_str);

          cout<<temp_str<<" ";
        }
        cout<<endl;
        pht_ff_group.push_back(temp_vec);
      }
      //extract e phrase group
      cout<<"extract e phrase group"<<endl;
      vector<WordIndex> es;
      //es.push_back(0);
      istringstream buffer_en(hstr_cur);
      while(buffer_en>>temp_str){
        es.push_back(EList[temp_str]);

        cout<<temp_str<<" ";
      }
      cout<<endl;

      for(int i=0;i < NT;i++){
        cout<<"==>handling hstr:"<<hstr_cur<<" line:"<<i+1;
        vector<string>& f_temp_sent = pht_ff_group[i];
        map<int, vector<int> >& map_temp_sent = pht_alfe_group[i];
        double group_prob = 0;
        for(int j=0;j < NT;j++){
          if (i!= j){
            //cout<<"dealing with ("<<i+1<<","<<j+1<<")";
            vector<string>& ft_temp_sent = pht_ff_group[j];
            vector<string> lsda_temp_sent;
            lsda_pht(f_temp_sent, ft_temp_sent, lsda_temp_sent);

            double sent_prob = 1;
            for(int rr=0;rr < lsda_temp_sent.size();rr++){
              istringstream buffer_ffid(lsda_temp_sent[rr]);
              string fr_str, ft_str;
              if( !((buffer_ffid>>fr_str)&&(buffer_ffid>>ft_str)) ){
                cerr<<"ERROR: decoding "<<i<<" "<<j<<" "<<hstr_cur<<" "<<rr<<" part"<<endl;
                exit(1);
              }
              WordIndex fr_id = FList[fr_str];
              WordIndex ft_id = FList[ft_str];
              if(map_temp_sent.find(rr) != map_temp_sent.end()){
                vector<int>& eid_vec = map_temp_sent[rr];
                double tmp_score = 0.0;
                for(int ast=0;ast < eid_vec.size();ast++){
                  WordIndex e_id = es[eid_vec[ast]];
                  if( t_ffe.find( FFEPair(fr_id, ft_id, e_id) ) != t_ffe.end() )
                    tmp_score += t_ffe[ FFEPair(fr_id, ft_id, e_id) ].prob;
                  else
                    tmp_score += 0.1e-10;
                }
                tmp_score /= eid_vec.size();
                sent_prob *= tmp_score;
              }
              else{
                WordIndex e_id = 0;
                if( t_ffe.find( FFEPair(fr_id, ft_id, e_id) ) != t_ffe.end() )
                    sent_prob *= t_ffe[FFEPair(fr_id, ft_id, e_id)].prob;
                else
                    sent_prob *= 0.1e-10;
              }
    	    	}

            group_prob += sent_prob;
            //cout<<" prob: "<<sent_prob<<endl;
          }//end of if
        }//end of for j 0...NT-1

        //output the result
        //pht_map[hstr_cur][i][2] += zsDouble2String(group_prob) + " ";
        cout<<" prob:"<<group_prob/NT<<endl;
        vector<string>& opv = pht_map[hstr_cur][i];
        for(int kk=0;kk < opv.size();kk++){
          if (kk == 2){
            of_npht<<opv[2]<<group_prob/NT<<" |||";
          }
          else{
            of_npht<<opv[kk]<<"|||";
          }
        }
        of_npht<<endl;

      }

      //decode algorithm end, ending process
      pht_map.clear();
      if (if_getl){
        hstr_cur = hstr;
        if(pht_map.find(hstr) != pht_map.end()){
          cerr<<"ERROR: hstr "<<hstr<<"  already in the pht_map "<<endl;
          exit(1);
        }
        pht_map[hstr].push_back(pht_line_vec);
      }

    }//end of else

    if (!if_getl)
      break;
  }//end of while
  cout<<"There are "<<cnt_lines<<" lines in file "<<fn_pht<<" and "<<cnt_single<<" single phrase"<<endl;

}



void RankModel::Decoder_na(string en_name, string fr_name, int N, vector<vector<fs_logp> >& logp_record, const char* fn_tffe, const char* fn_tst_ff){
  /* reading t(f, f'|e) from fn_tffe file */
  read_tffe(fn_tffe);

  /* reading corpus */
  cout<<"......decode Initialization......"<<endl;
  ifstream in_en(en_name.c_str());
  if(!in_en){
    cerr<<"ERROR: cannot open file "<<en_name<<endl;
    exit(1);
  }
  ifstream in_tst_ff(fn_tst_ff);
  if(!in_tst_ff){
    cerr<<"ERROR: cannot open file "<<fn_tst_ff<<endl;
    exit(1);
  }
  string en_line, fr_line, temp_string;

  cout<<"......reading "<<en_name<<" test corpus......"<<endl;
  //reading en corpus
  while(getline(in_en, en_line)){
    vector<WordIndex> en_temp_sent;
    en_temp_sent.push_back(0);
    istringstream buffer_en(en_line);
    while(buffer_en>>temp_string){
      en_temp_sent.push_back( EList[temp_string] );
    }
    decode_en.push_back(en_temp_sent);
  }

  cout<<"......reading "<<fr_name<<" test corpus from file "<<fn_tst_ff<<endl;
  //reading fr corpus
  WordIndex f_id, ft_id;
  while(getline(in_tst_ff, fr_line)){
    vector<FPair> ff_temp_sent;
    istringstream buffer_ff(fr_line);
    while(buffer_ff>>f_id>>ft_id){
      ff_temp_sent.push_back( FPair(f_id, ft_id) );
    }
    decode_ff.push_back(ff_temp_sent);
  }

  //Calculate the important length
  int Total_len = decode_ff.size();
  int Group_len = Total_len / N;
  int Block_len = Group_len / (N-1);
  cout<<"Total_len : "<<Total_len<<"  Group_len : "<<Group_len<<"  Block_len : "<<Block_len<<endl;

  //initialize the logp_record
  logp_record.clear();
  vector<fs_logp> ztv_tmp;
  logp_record.push_back(ztv_tmp);
  for(int i=1;i <= N;i++){
    vector<fs_logp> itv_tmp( Block_len, fs_logp(i, 0.0) );
    logp_record.push_back(itv_tmp);
  }

  /*Running decoding algorithm*/
  cout<<"......RankModel Decoding......"<<endl;
  double sent_logp, temp_s, temp_pp;
  WordIndex temp_index;
  for(int i=1;i <= N;i++){
    for(int j=1;j <= N-1;j++){
      for(int k=0;k < Block_len;k++){
        vector<FPair>& ffs_v = decode_ff[ (i-1)*Group_len + (j-1)*Block_len + k ];
        vector<WordIndex>& es_v = decode_en[k];
        sent_logp = 1;
        for(int rr=0;rr < ffs_v.size();rr++){
          WordIndex fr_id = ffs_v[rr].f_id;
          WordIndex ft_id = ffs_v[rr].ft_id;

          temp_s = 0;
          for(int cc=0;cc < es_v.size();cc++){
            if(t_ffe.find( FFEPair(fr_id, ft_id, es_v[cc]) ) == t_ffe.end())
              temp_pp = 0.1e-10;
            else
              temp_pp = t_ffe[ FFEPair( fr_id, ft_id, es_v[cc] ) ].prob;

            if(temp_pp > temp_s){
              temp_s = temp_pp;
              temp_index = cc;
            }
          }
          sent_logp *= temp_s;
        }
        logp_record[i][k].logp += sent_logp;
      }
    }
  }
  cout<<"......Decode Successful......"<<endl;

}



void RankModel::print_tffe(const char* fn_tffe){
  cout<<"......print t(f, f'|e) information to file "<<fn_tffe<<"......"<<endl;
  ofstream of_tffe(fn_tffe);

  int nocnt = 0;
	hash_map<FFEPair, CPPair, hash_ffe, equal_ffe>::iterator pt = t_ffe.begin();
  for(pt=t_ffe.begin();pt != t_ffe.end();pt++){
    nocnt++;
    of_tffe<<(*pt).first.fr_id<<"  "<<(*pt).first.frtr_id<<"  "<<(*pt).first.en_id<<"    "<<(*pt).second.prob<<"\n";
  }
  cout<<"......there are "<<nocnt<<" lines in total......."<<endl;
}





void RankModel::decode2(string en_name, string lsda_name, int no, vector<fs_logp>& ffe_logp){
	ifstream in_en(en_name.c_str());
	ifstream in_lsda(lsda_name.c_str());
	string en_line, lsda_line;
	WordIndex i, j, l, m, temp_index;
	double temp, temp_pp;
	int nosent = 0;
	unsigned int rs = 1000;
	cout<<"...decoding......calculate the log probability of f_f_e in sentence level......"<<endl;

	while(getline(in_en, en_line) && getline(in_lsda, lsda_line) ){
		double sent_logp = 0;
		istringstream en_buffer(en_line);
		istringstream lsda_buffer(lsda_line);
		vector<WordIndex> es;
		es.push_back(0);
		vector<FPair> ffs;
		ffs.push_back(FPair(0, 0));

		string en_str, fr_str, frt_str;
		while((en_buffer>>en_str) && (lsda_buffer>>fr_str) && (lsda_buffer>>frt_str)){
			WordIndex en_id, fr_id, frt_id;
			es.push_back(EList[en_str]);
			ffs.push_back( FPair( FList[fr_str], FList[frt_str] ));
		}
		l = es.size() - 1;
		m = ffs.size() - 1;
		for(i=1;i <= m;i++){
			temp = 0;
			for(j=0;j <= l;j++){
				if(t_ffe.find(FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])) == t_ffe.end())
					temp_pp = 0.1e-10;
				else
					temp_pp = t_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob;
				if(temp_pp > temp){
					temp = temp_pp;
				}
			}
			sent_logp += log(temp);
		}
		if(ffe_logp.size() < rs)
			ffe_logp.push_back(fs_logp(no, sent_logp));
		else
			ffe_logp[nosent].logp += sent_logp;
		nosent++;
		cout<<nosent<<" ";
	}
	cout<<endl;

}





void RankModel::print_align(ofstream& of){
	WordIndex i, j, l, m, temp_index;
	double temp, temp_pp;
	cout<<"output result to the rank_alignment file"<<endl;

	for(unsigned int k=0;k < rankcorpus.size();k++){
		RankSent& temp_sent = rankcorpus[k];
		vector<WordIndex>& es = temp_sent.esent;
		vector<FPair>& ffs = temp_sent.ffsent;
		l = es.size() - 1;
		m = ffs.size() - 1;
		vector<WordIndex> al_ij;
		al_ij.push_back(0);
		for(i=1;i <= m;i++){
			temp = 0;
			for(j=0;j <= l;j++){
				temp_pp = info_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob * info_fe[WordPairIds(ffs[i].ft_id, es[j])].prob;
				if(temp_pp > temp){
					temp = temp_pp;
					temp_index = j;
				}
			}
			al_ij.push_back(temp_index);
		}

		of<<"#sentence pair ("<<temp_sent.noSent<<") f sentence length "<<m<<", e sentence length "<<l<<"\n";
		for(i=1;i <= m;i++)
			of<<FList[ffs[i].f_id]<<" ";
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

void RankModel::cal_logp(int no, vector<fs_logp>& ffe_logp){

	WordIndex i, j, l, m, temp_index;
	double temp, temp_pp;
	cout<<"......calculate the log probability of f_f_e in sentence level......"<<endl;
	unsigned int rs = rankcorpus.size();

	for(unsigned int k=0;k < rs;k++){
		double sent_logp = 0;
		RankSent& temp_sent = rankcorpus[k];
		vector<WordIndex>& es = temp_sent.esent;
		vector<FPair>& ffs = temp_sent.ffsent;
		l = es.size() - 1;
		m = ffs.size() - 1;
		for(i=1;i <= m;i++){
			temp = 0;
			for(j=0;j <= l;j++){
				temp_pp = info_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob * info_fe[WordPairIds(ffs[i].ft_id, es[j])].prob;
				if(temp_pp > temp){
					temp = temp_pp;
				}
			}
			sent_logp += log(temp);
		}
		if(ffe_logp.size() < rs)
			ffe_logp.push_back(fs_logp(no, sent_logp));
		else
			ffe_logp[k].logp += sent_logp;
	}
}



void RankModel::cal_tffe1(const char* pct){
	cout<<"calculate t(f, f'|e)"<<endl;

	WordIndex i, j, l, m, temp_index;
	double temp, temp_pp;

	for(unsigned int k=0;k < rankcorpus.size();k++){
		RankSent& temp_sent = rankcorpus[k];
		vector<WordIndex>& es = temp_sent.esent;
		vector<FPair>& ffs = temp_sent.ffsent;
		l = es.size() - 1;
		m = ffs.size() - 1;
		vector<WordIndex> al_ij;
		al_ij.push_back(0);
		for(i=1;i <= m;i++){
			for(j=0;j <= l;j++){
				t_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob = info_ffe[FFEPair(ffs[i].f_id, ffs[i].ft_id, es[j])].prob * info_fe[WordPairIds(ffs[i].ft_id, es[j])].prob;
			}
		}

	}
}





