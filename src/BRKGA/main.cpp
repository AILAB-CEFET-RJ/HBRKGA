#include <iostream>
#include <stdio.h>
#include "AG.h"

using namespace std;

int main(){

	cout<<"Começou!"<<endl;

	AG Meta(100,1000,0.2,0.1,0.7,1,1,0,0,100,2,1000);

	Meta.solve();

	cout<<"Terminou!"<<endl;

	return 0;	
}
