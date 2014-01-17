
#include "model12.h"

void model12::initialization(){
	WordIndex i, j, l, m;
	SentPair sent;
	sHander.new_start();
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
					sum += cal_ef[WordPairIds(es[j], fs[i])].prob;
				for(j=0;j <= l;j++){
					temp = cal_ef[WordPairIds(es[j], fs[i])].prob/sum;
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
				}//end of for j
			}//end of for i
		}//end of while
	}//end of for iteration
}


void model12::print_tfe(const char* cooc_f, ofstream& of){
	ifstream in_cooc(cooc_f);
	string line;
	WordIndex noew, nofw;
	map<WordIndex, double> kk;
	while(getline(in_cooc, line)){
		istringstream ef_buffer(line);
		if(ef_buffer>>noew>>nofw){
		    kk[noew] += cal_ef[WordPairIds(noew, nofw)].prob;
			of<<noew<<" "<<nofw<<" "<<cal_ef[WordPairIds(noew, nofw)].prob<<" "<<kk[noew]<<"\n";
		}
	}
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

