#include<iostream>
#include<stdlib.h>

#include "solution.h"
#include "BRKGA/AG.h"
#include "FWChrono.h"
#include "ES.h"
#include "path_relinking.h"
#include <time.h>

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
		//seed = 123;

		Tempo.start();
		cout<<"Vai comecar o Algoritmo Genetico"<<endl;
		AG Meta(EliteSet,num_par,10,0.2,0.1,0.7,1,1,seed,0,2,5,6); //Populacao tamanho 10 com 6 geracoes Random Walk
		Meta.solve();
		cout<<"Acabou o Algoritmo Genetico!"<<endl;

		//cout<<*EliteSet<<endl;

		//PathRelinking * PR = new PathRelinking(EliteSet);

		//Solution* BestSol;

		//BestSol = PR->solve(Meta.getBest());

		Tempo.stop();

		cout<<"--------------------------------------------------"<<endl;
		cout<<Meta.getBest()<<endl;
		cout<<Tempo.getStopTime()<<endl;
		cout<<"--------------------------------------------------"<<endl;

		//delete PR;
		//delete BestSol;
		delete EliteSet;
	}

	return 0;
}
