#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <iostream>
#include <utility>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

class Solution
{
private:
	vector<double> par_set;
	double cost;
	unsigned long hash;
	friend ostream& operator<<(ostream&, const Solution&);

public:

	friend bool operator< (Solution &a, Solution &b);
	friend bool operator> (Solution &a, Solution &b);
	friend bool operator== (Solution &a, Solution &b);


	Solution();

	~Solution();

	double get_cost();
	void set_cost(double i);

	vector<double>& get_param(){return par_set;};

	void change_param(double i, int j);
	void add_param(double i);
	void set_hash(double i);

	 bool operator()(const Solution& a,const Solution& b) const{
	    return(a.cost<b.cost);
	 }


};



#endif //SOLUTION_H_
