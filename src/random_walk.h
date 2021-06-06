#ifndef RANDOM_WALK_H_
#define RANDOM_WALK_H_

#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <sstream>
#include <fstream>
#include <iostream>
#include <utility>
#include <time.h>

using namespace std;


class RandomWalk
{
	private:
		static vector<int> mov;
		vector< pair<double,double> > par_dom;

		random_device rd;
		mt19937 * mt;

	public:
		RandomWalk(vector< pair<double,double> > pardom){
			mt = new mt19937 (time(0));
			par_dom = pardom;
		};
		~RandomWalk(){delete mt;};

		double search(double * p, int size=5, int N = 3);
		double evaluate(const double * const p, int size=5);

};


#endif //RANDOM_WALK_H_
