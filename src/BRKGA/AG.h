#include <iostream>
#include "SampleDecoder.h"
#include "MTRand.h"
#include "BRKGA.h"
#include "../FWChrono.h"
#include "../ES.h"
class AG{
	private:
	vector< pair<double,double> > par_dom;

	unsigned n;		// size of chromosomes
	unsigned p;	// size of population ------populacao---------
	double pe;		// fraction of population to be the elite-set
	double pm;		// fraction of population to be replaced by mutants
	double rhoe;	// probability that offspring inherit an allele from elite parent
	unsigned K;		// number of independent populations
	unsigned MAXT;	// number of threads for parallel decoding
	unsigned timelimit;
	SampleDecoder* decoder;			// initialize the decoder
	ES * EliteSet;
	RandomWalk * BL;
	long unsigned rngSeed;	// seed to the random number generator
	MTRand * rng;				// initialize the random number generator

	// initialize the BRKGA-based heuristic
	BRKGA< SampleDecoder, MTRand > * algorithm;

	unsigned generation;		// current generation
	unsigned X_INTVL;	// exchange best individuals at every 100 generations
	unsigned X_NUMBER ;	// exchange top 2 best
	unsigned MAX_GENS;	// run for 1000 gens

	public:
	AG(ES * _EliteSet, unsigned _n, unsigned _p, double _pe, double _pm, 
		double _rhoe, unsigned _K, unsigned _MAXT, long unsigned _rngSeed, 
		unsigned _generation, unsigned _X_INTVL, unsigned _X_NUMBER, 
		unsigned _MAX_GENS, vector< pair<double,double> > pardom) {

		
	n=_n;
	p=_p;
	pe=_pe;
	pm=_pm;
	rhoe=_rhoe;
	K=_K;
	MAXT=_MAXT;
	rngSeed=_rngSeed;
	generation=_generation;
	X_INTVL=_X_INTVL;
	X_NUMBER=_X_NUMBER;
	MAX_GENS=_MAX_GENS;
	EliteSet = _EliteSet;
	par_dom = pardom;

	BL = new RandomWalk(par_dom);
	rng = new MTRand(rngSeed);
	
	decoder = new SampleDecoder(EliteSet, BL, par_dom);
	
	algorithm = new BRKGA< SampleDecoder, MTRand > (n, p, pe, pm, rhoe, (*decoder), (*rng), K, MAXT);

	};

	~AG(){
		delete(BL);
		delete(algorithm);
		delete(decoder);

	};

	void solve(){
		FWChrono Tempo;
		Tempo.start();
		do {
			cout<<"Starting generation number " << generation+1 <<endl;
			algorithm->evolve();	// evolve the population for one generation
			
			if((++generation) % X_INTVL == 0) {
				algorithm->exchangeElite(X_NUMBER);	// exchange top individuals
			}
			
			cout<< getBest()<<endl;
			cout<<"End of generation number " << generation <<endl;
		} while (generation < MAX_GENS);

		std::cout << "Best Solution HBRKGA = "	<< -algorithm->getBestFitness() << std::endl;
		Tempo.stop();
	};

	Solution getBest(){
		int cont=0;
		vector<double> bestsol = algorithm->getBestChromosome();
		Solution BS;
		for(auto it = bestsol.begin(); it!= bestsol.end(); it++){
			BS.add_param(*it*(par_dom[cont].second-par_dom[cont].first) + par_dom[cont].first);
			cont++;
		}
		BS.set_cost(-algorithm->getBestFitness());
		return BS;
	}

};
