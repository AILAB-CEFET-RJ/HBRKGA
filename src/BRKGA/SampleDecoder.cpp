/*
 * SampleDecoder.cpp
 *
 *  Created on: Jan 14, 2011
 *      Author: rtoso
 */

#include "SampleDecoder.h"

#define Infinity 99999999999999

SampleDecoder::SampleDecoder(ES * _EliteSet, RandomWalk* _BL,
		vector< pair<double,double> > pardom){
	par_dom = pardom;
	EliteSet = _EliteSet;
	BL = _BL;
}

SampleDecoder::~SampleDecoder() {

}


double SampleDecoder::decode(std::vector< double >& chromosome) const {
	unsigned n = chromosome.size();
	double * parameter = new double [n];

	Solution sol;
	for (unsigned i = 0; i < n; ++i) {
		if(i>2){
			parameter[i] = ceil((chromosome[i] * (par_dom[i].second-par_dom[i].first) + par_dom[i].first)*1000000)/1000000;
		}else{
			parameter[i] = ceil(chromosome[i] * (par_dom[i].second-par_dom[i].first) + par_dom[i].first);
		}
	}
	double fitness = BL->search(parameter);

	for (unsigned i = 0; i < n; ++i) {
		sol.add_param(parameter[i]);
		chromosome[i] = parameter[i]/((par_dom[i].second-par_dom[i].first) + par_dom[i].first);
	}

	sol.set_cost(fitness);

	cout<< "Best Random-Walk solution: \n"<<sol << "\n" <<endl;

	EliteSet->add(sol);

	delete[] parameter;

	return -fitness;
}
