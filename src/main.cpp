#include<iostream>
#include<stdlib.h>

#include "solution.h"
#include "BRKGA/AG.h"
#include "FWChrono.h"
#include "ES.h"
#include "path_relinking.h"
#include <time.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;
namespace py = pybind11;
using namespace pybind11::literals;

using namespace std;

void usage(char *argv[]){
	cout << "Usage:" <<endl;
	cout << "\t"<<argv[0]<<endl;
}

int hbrkga(py::list params, py::dict ga_params) {
	// vector< pair<double,double> > pardom = {{1000,2000},{2000,4000},{2000,6000},{1E-6,1E-1},{0,1E-3}};

	std::vector<std::pair<double,double>> pardom = params.cast<std::vector<std::pair<double, double>>>();
	std::cout << "Parameters to be optimized" << std::endl;
	for(const pair<double,double> &i : pardom){
		cout << i.first << " " << i.second << endl;
	}
	std::cout << std::endl;

	size_t eg;
	unsigned n;
	unsigned p;
	double pe;
	double pm;
	double rhoe;
	unsigned k;
	unsigned maxT;
	long unsigned rngSeed;
	unsigned generation;
	unsigned xIntvl;
	unsigned xNumber;
	unsigned maxGens;
	
	// Genetic Algorithm parameters parsing
	for(auto param : ga_params) {
		std::string key = std::string(py::str(param.first));
		if(key == "eg"){
			eg = param.second.cast<size_t>();
		} else if(key == "n"){
			n = param.second.cast<int>();
		} else if(key == "p"){
			p = param.second.cast<int>();
		} else if(key == "pe"){
			pe = param.second.cast<double>();
		} else if(key == "pm"){
			pm = param.second.cast<double>();
		} else if(key == "rhoe"){
			rhoe = param.second.cast<double>();
		} else if(key == "k"){
			k = param.second.cast<int>();
		} else if(key == "maxT"){
			maxT = param.second.cast<int>();
		} else if(key == "rngSeed"){
			rngSeed = param.second.cast<long>();
		} else if(key == "generation"){
			generation = param.second.cast<int>();
		} else if(key == "xIntvl"){
			xIntvl = param.second.cast<int>();
		} else if(key == "xNumber"){
			xNumber = param.second.cast<int>();
		} else if(key == "maxGens"){
			maxGens = param.second.cast<int>();
		}
	}
	
	std::cout << "Genetic Algorithm parameters" << std::endl;
	std::cout << "eg: " << eg << std::endl;
	std::cout << "n: " << n << std::endl;
	std::cout << "p: " << p << std::endl;
	std::cout << "pe: " << pe << std::endl;
	std::cout << "pm: " << pm << std::endl;
	std::cout << "rhoe: " << rhoe << std::endl;
	std::cout << "k: " << k << std::endl;
	std::cout << "maxT: " << maxT << std::endl;
	std::cout << "rngSeed: " << rngSeed << std::endl;
	std::cout << "generation: " << generation << std::endl;
	std::cout << "xIntvl: " << xIntvl << std::endl;
	std::cout << "xNumber: " << xNumber << std::endl;
	std::cout << "maxGens: " << maxGens << std::endl;
	// Genetic Algorithm parameters parsing - end

	FWChrono Tempo;
	ES* EliteSet = new ES (eg);

	cout << "Começou!" << endl;
	AG Meta(EliteSet, n, p, pe, pm, rhoe, k, maxT, rngSeed, generation, xIntvl, xNumber,
					maxGens, pardom);

	Meta.solve();

	Tempo.stop();

	cout<<"--------------------------------------------------"<<endl;
	cout<<Meta.getBest()<<endl;
	cout<<Tempo.getStopTime()<<endl;
	cout<<"--------------------------------------------------"<<endl;

	delete EliteSet;

	cout << "Terminou!" << endl;

	return 0;
}

PYBIND11_MODULE(hbrkga, m) {
    m.doc() = "HBRKGA module"; // optional module docstring

    m.def("hbrkga", &hbrkga, "HBRKGA main function");
}