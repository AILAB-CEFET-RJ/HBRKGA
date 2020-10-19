#ifndef ES_CPP_
#define ES_CPP_

#include "ES.h"

struct compare_sol {
    bool operator()(Solution a, Solution b) const {
    	if(a.get_cost()-b.get_cost()<1E-5 || b.get_cost()-a.get_cost()>-1E-5)return false;
    		return a.get_cost()>b.get_cost();
    }
};


ES::ES(size_t _MaxSize){
	MaxSize = _MaxSize;
}

ES::~ES(){

}

size_t ES::getESsize(){
	return HeapSol.size();
}

bool ES::add(Solution s){
	//cout<<"inserindo no ES ...."<<endl;

	for(size_t i=0; i<HeapSol.size(); ++i){
		if(HeapSol.at(i)==s)
			return false;
		//cout << sol<<endl;
	}

	//cout<<"nao achou igual, vou tentar inserir"<<endl;

	//if(find(HeapSol.begin(),HeapSol.end(),*s) != HeapSol.end())
	//	return false;

	Solution* WorstSol;
	//cout<<"adding: "<<*s<<endl;
	if(HeapSol.size() == 0){
		WorstSol = NULL;
	}else{
		WorstSol = &HeapSol.front();

		//cout<<*WorstSol<<endl;
	}

	if(HeapSol.size() < MaxSize ){
		//cout<<"inserindo tamanho menor"<<endl;
		//ConjSol.insert(s);
		//cout<<"inseriu"<<endl;
		HeapSol.push_back(s);
		push_heap (HeapSol.begin(),HeapSol.end(),compare_sol());

		return true;
	}else if(s.get_cost() > WorstSol->get_cost()){
		//cout<<"inserindo tamanho maior"<<endl;
		//ConjSol.erase(HeapSol.front());
		pop_heap (HeapSol.begin(),HeapSol.end(),compare_sol());
		HeapSol.pop_back();

		//ConjSol.insert(s);
		//cout<<"inseriu2"<<endl;

		HeapSol.push_back(s);
		push_heap (HeapSol.begin(),HeapSol.end(),compare_sol());

		return true;
	}

	return false;
}

vector<Solution> ES::getConjSol(){
	return HeapSol;
}


ostream& operator<<(ostream &strm, ES es){

	for(size_t i=0; i<es.HeapSol.size(); ++i){
		strm<<es.HeapSol.at(i)<<endl;
		//cout << sol<<endl;
	}
	return strm;
}

#endif // ES_CPP_
