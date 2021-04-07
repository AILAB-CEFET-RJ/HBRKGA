#include <iostream>
#include <stdio.h>
#include "AG.h"

using namespace std;

int main()
{

	cout << "Começou!" << endl;

	AG Meta(100, 1000, 0.2, 0.1, 0.7, 1, 1, 0, 0, 100, 2, 1000);

	Meta.solve();

	cout << "Terminou!" << endl;

	return 0;
}

int my_main(unsigned n, unsigned p, double pe, double pm, double rhoe,
				 unsigned k, unsigned maxT, long unsigned rngSeed, unsigned generation,
				 unsigned xIntvl, unsigned xNumber, unsigned maxGens)
{

	cout << "Começou!" << endl;
	AG Meta(n, p, pe, pm, rhoe, k, maxT, rngSeed, generation, xIntvl, xNumber,
					maxGens);

	Meta.solve();

	cout << "Terminou!" << endl;
}