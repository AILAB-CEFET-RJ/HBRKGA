/*
 * SampleDecoder.cpp
 *
 *  Created on: Jan 14, 2011
 *      Author: rtoso
 */

#include "SampleDecoder.h"

#define Infinity 99999999999999

SampleDecoder::SampleDecoder(ES * _EliteSet, RandomWalk* _BL){
	par_dom.push_back(make_pair(1000,2000));
	par_dom.push_back(make_pair(2000,4000));
	par_dom.push_back(make_pair(2000,6000));
	par_dom.push_back(make_pair(0.000001,0.1));
	par_dom.push_back(make_pair(0,0.001));
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
	/*
	for (unsigned i = 0; i < n; ++i) {
		sol.add_param(parameter[i]);
		if (i>2){
			chromosome[i] = ceil((parameter[i]/((par_dom[i].second-par_dom[i].first) + par_dom[i].first))*1000000)/1000000;
		} else {
			chromosome[i] = ceil(parameter[i]/((par_dom[i].second-par_dom[i].first) + par_dom[i].first));
		}
	} */

	for (unsigned i = 0; i < n; ++i) {
		sol.add_param(parameter[i]);
		chromosome[i] = parameter[i]/((par_dom[i].second-par_dom[i].first) + par_dom[i].first);
	}

	sol.set_cost(fitness);

	cout<<sol<<endl;
	//cout<<"fitness"<<fitness<<endl;

	EliteSet->add(sol);

	delete[] parameter;

	return -fitness;
}
