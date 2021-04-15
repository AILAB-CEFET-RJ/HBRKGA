#include<iostream>
#include<stdlib.h>

#include "solution.h"
#include "BRKGA/AG.h"
#include "FWChrono.h"
#include "ES.h"
#include "path_relinking.h"
#include <time.h>
#include <pybind11/pybind11.h>

using namespace std;
namespace py = pybind11;
using namespace pybind11::literals;

using namespace std;

void usage(char *argv[]){
	cout << "Usage:" <<endl;
	cout << "\t"<<argv[0]<<endl;
}


int main(int argc, char *argv[]){

	if(argc!=1){
		usage(argv);
	}else{

		FWChrono Tempo;
		ES* EliteSet = new ES (5);
		unsigned num_par=5;
		time_t seed;
		srand(time(0)); 
		seed = time(0);

		Tempo.start();
		AG Meta(EliteSet,num_par,10,0.2,0.1,0.7,1,1,seed,0,2,5,6); 
		//Pop size 10 / 6 generations plus RW
		Meta.solve();

		Tempo.stop();

		cout<<"--------------------------------------------------"<<endl;
		cout<<Meta.getBest()<<endl;
		cout<<Tempo.getStopTime()<<endl;
		cout<<"--------------------------------------------------"<<endl;

		delete EliteSet;
	}
	return 0;
}


int hbrkga(size_t eg, unsigned n, unsigned p, double pe, double pm, double rhoe,
				 unsigned k, unsigned maxT, long unsigned rngSeed, unsigned generation,
				 unsigned xIntvl, unsigned xNumber, unsigned maxGens)
{

	FWChrono Tempo;
	ES* EliteSet = new ES (eg);

	cout << "Começou!" << endl;
	AG Meta(EliteSet, n, p, pe, pm, rhoe, k, maxT, rngSeed, generation, xIntvl, xNumber,
					maxGens);

	Meta.solve();
		//Pop size 10 / 6 generations plus RW
	Meta.solve();

	Tempo.stop();

	cout<<"--------------------------------------------------"<<endl;
	cout<<Meta.getBest()<<endl;
	cout<<Tempo.getStopTime()<<endl;
	cout<<"--------------------------------------------------"<<endl;

	delete EliteSet;

	cout << "Terminou!" << endl;
}

PYBIND11_MODULE(hbrkga, m) {
    m.doc() = "HBRKGA module"; // optional module docstring

    m.def("hbrkga", &hbrkga, "HBRKGA main function", "eg"_a=5,
      "n"_a=100, "p"_a=1000, "pe"_a=0.2, "pm"_a=0.1, "rhoe"_a=0.7, 
			"k"_a=1, "maxT"_a=1, "rngSeed"_a=0, "generation"_a=0, 
			"xIntvl"_a=100, "xNumber"_a=2, "maxGens"_a=1000
		);
}