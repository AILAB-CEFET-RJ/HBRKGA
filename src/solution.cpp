#ifndef SOLUTION_CPP_
#define SOLUTION_CPP_

#include "solution.h"

Solution::Solution(){
	cost = 0;
	hash = 0;
}

Solution::~Solution(){
}

void Solution::set_cost(double i){
	cost = i;
}

double Solution::get_cost(){
	return cost;
}

void Solution::add_param(double i){
	par_set.push_back(i);
	set_hash(i);
}

void Solution::set_hash(double i){
	hash+=(i+1)*(i+2);
}

void Solution::change_param(double i, int j){
	par_set[j] = i;
}


ostream& operator<<(ostream& strm, const Solution& s){
	vector<double> grupo=s.par_set;
	vector<double>::iterator it;
	for(it = grupo.begin(); it!=grupo.end(); ++it){
		strm<< *it <<" ";
	}
	strm<<"\n"<<s.cost;
	return strm;
}


bool operator== (Solution &a, Solution &b){
	if(a.cost != b.cost){
		//cout<<"é true! "<<a.cost<<" "<<b.cost<<endl;
		return false;
	}

	if(a.hash != b.hash) return false;
	vector<double>::iterator it2 = b.par_set.begin();
	for(vector<double>::iterator it = a.par_set.begin(); it!=a.par_set.end(); ++it){
			if(*it!=*it2) return false;
			++it2;
	}


	return true;
}

bool operator< (Solution &a, Solution &b){
	//cout<<"Testa Menor"<<endl;

	if(a.cost<b.cost) return true;
	if(a.hash < b.hash) return true;
	return false;
}

bool operator> (Solution &a, Solution &b){
	//cout<<"Testa Maior"<<endl;

	if(a.cost>b.cost) return true;
	if(a.hash > b.hash) return true;

	return false;
}

#endif // SOLUTION_CPP_it2 = p.Neighbor[*it].begin()
