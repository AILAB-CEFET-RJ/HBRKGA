#ifndef PATH_RELINKING_H_
#define PATH_RELINKING_H_

#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <utility>
#include "solution.h"
#include "ES.h"

using namespace std;


class PathRelinking
{
private:

	ES* EliteSet;

public:

	PathRelinking(ES* _EliteSet);

	~PathRelinking();

	Solution * solve(Solution GuideSol);

	int getBestPRSol(vector<Solution>& lista,double& cost);
	int GenPath(Solution Guide, Solution Arrive, vector<Solution> &GenerateNewElite, int index=0, int size=5);
	double evaluate(double* param, int size=5);
	bool NotinTheSet(Solution& Sol, vector<Solution> &GenerateNewElite);
	bool is_equal(Solution& a, Solution& b);
};


#endif //PATH_RELINKING_H_
