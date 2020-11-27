#ifndef RANDOM_WALK_CPP_
#define RANDOM_WALK_CPP_

#include"random_walk.h"

vector<int>  RandomWalk::mov = {-15,-10,-5,5,10,15};

double RandomWalk::search(double * p, int size, int N){
  double * base = new double [size];
  double diff=0;
  double base_mov=0;

  uniform_int_distribution<int> distribution(0.0,size-1);
  uniform_int_distribution<int> distribution_v(0.0,mov.size()-1);

  int index=0;
  double perc=1.0, cost=0, bcost=0;

  for(int i = 0; i<size; i++){
    base[i] = p[i];
  }

  bcost = evaluate(base,size);

//(Round Robin)
  for(int i=0; i<N; i++){
    index = distribution(*mt);
    perc =  0.1+mov[distribution_v(*mt)]/100.0;
    cout << "percentage " << perc << endl;
    cout << "movement " << mov[distribution_v(*mt)] << endl;
    cout << "first " << par_dom[index].first << endl;
    cout << "second " << par_dom[index].second << endl;
    cout << "base[index] " << base[index] << endl;
    cout << "index " << index << endl;
    base_mov = base[index] + (base[index] * perc);
    cout << "base_mov " << base_mov << endl;

    if( base_mov > par_dom[index].second){
      diff = base_mov - par_dom[index].second;
      base[index] = par_dom[index].first + diff;
      cout << "Round Robin " << endl;
    }
    else if(base_mov < par_dom[index].first) {
      diff = par_dom[index].first - base_mov;
      base[index] = par_dom[index].first + diff;
      cout << "Round Robin " << endl;
    }

    if (index>2) {
         base[index] = ceil((base_mov) * 1000000)/1000000;
      } else if (index<=2) {
          base[index] = ceil(base_mov);
      }

    cost = evaluate(base,size);
    if(cost>bcost){
      p[index] = base[index];
      bcost = cost;
    }
  } //End Roud Robin


 //(Min ou Max)
  /*for(int i=0; i<N; i++){
    index = distribution(*mt);
    //cout << "index " << index << endl;
    perc =  0.1+mov[distribution_v(*mt)]/100.0;

    if( base[index] * perc > par_dom[index].second)
      base[index] = par_dom[index].second;
    else if(base[index] * perc < par_dom[index].first)
      base[index] = par_dom[index].first;
    else if (index>2)
      {
         //base[index] = base[index] * perc; 
         base[index] = ceil((base[index] * perc) * 1000000)/1000000;
      } else if (index<2) {
          base[index] = ceil(base[index] * perc);
      }

    cost = evaluate(base,size);
    if(cost>bcost){
      p[index] = base[index];
      bcost = cost;
    }
  } */
 //(Min ou Max)

  delete[] base;
	return bcost;
}

double RandomWalk::evaluate(const double * const p, int size){
	cout << "***Solution: " <<p[0] << " " << p[1] << " " << p[2] << " " << p[3] << " " << p[4] << endl;
	ostringstream buffer;
	buffer.str("");
	buffer	<< "python ./src/python/neural_network.py fashion"
			<< " "	<< p[0]
			<< " "	<< p[1]
			<< " "	<< p[2]
			<< " "	<< p[3]
			<< " "	<< p[4]
			<< " > ./src/python/saida.txt" ;
	int s = system(buffer.str().c_str());
	if(s != 0){ cerr << "ERROR: function system cannot be performed." << endl; exit(1);}
	buffer.str("");


	ifstream f_inst("src/python/saida.txt");
	if(!f_inst.is_open()){
		cout << "ERROR: File "<<"src/python/saida.txt"<<" not found!"<<endl;
		exit(0);
	}

	double solution;
	f_inst >> solution;

	f_inst.close();
  cout << "###Evaluated Solution: " << solution << "\n" <<endl;

	return solution;
}

#endif // RANDOM_WALK_CPP_
