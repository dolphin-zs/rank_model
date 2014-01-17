#include<iostream>
#include<fstream>
#include<sstream>

#include <ext/hash_set>
#include <ext/hash_map>
using namespace __gnu_cxx;

using namespace std;

const int MAX_W = 10;
typedef unsigned int WordIndex;

class FFEPair{
	public:
		WordIndex fr_id;
		WordIndex frtr_id;
		WordIndex en_id;
	
		FFEPair(WordIndex i, WordIndex j, WordIndex k):fr_id(i), frtr_id(j), en_id(k){}
		size_t getindex() const{
			return (size_t)fr_id*MAX_W*MAX_W + frtr_id*MAX_W + en_id;
		}
};
class hash_ffe{
	public:
		size_t operator()(const class FFEPair& x) const{
			return x.getindex();
		}
};
class equal_ffe{
	public:
		bool operator()(const class FFEPair& x, const class FFEPair& y) const{
			return (x.getindex() == y.getindex());
		}
};

int main(){
	hash_map<FFEPair, size_t, hash_ffe, equal_ffe> testhmap;
	hash_map<FFEPair, size_t, hash_ffe, equal_ffe>::iterator pt = testhmap.begin();
	for(int i=0;i <= 10;i++){
		FFEPair temp(i, i, i);
		testhmap[temp] = temp.getindex();
	}
	for(pt=testhmap.begin();pt != testhmap.end();pt++)
		cout<<(*pt).second<<" ";
	cout<<endl;

	return 0;
}












