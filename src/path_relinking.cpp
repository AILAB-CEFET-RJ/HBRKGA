#ifndef PATH_RELINKING_CPP_
#define PATH_RELINKING_CPP_

#include "path_relinking.h"

bool PathRelinking::is_equal(Solution& a, Solution& b){
	for(int i=0; i<a.get_param().size();++i){
		if(a.get_param()[i] != b.get_param()[i]) return false;
	}
	return true;
}

PathRelinking::PathRelinking(ES* _EliteSet){
	EliteSet = _EliteSet;
}

PathRelinking::~PathRelinking(){

}

Solution * PathRelinking::solve(Solution GuideSol){
	Solution * BestSol = new Solution();

	vector<Solution> ListElite = EliteSet->getConjSol();
	vector<Solution> GenerateNewElite;

	if(NotinTheSet(GuideSol,GenerateNewElite)){
		GenerateNewElite.push_back(GuideSol);
 	}

	for(vector<Solution>::iterator it = ListElite.begin();it!=ListElite.end();++it){
		//cout<<"-----------------New Go---------------"<<endl;
		if(!(GuideSol == *it)){
			/*cout<<"-----------------New Go---------------"<<endl;
			cout<<GuideSol<<endl;
			cout<<*it<<endl;
			cout<<"-------------Fim-New Go---------------"<<endl;
			*/
			if(NotinTheSet(*it,GenerateNewElite)){
				GenerateNewElite.push_back(*it);
				//cout<<"-------------OUT-------------"<<endl;
				//cout<<*it<<endl;
				//cout<<"-----------------------------"<<endl;
			}
			GenPath(GuideSol, *it, GenerateNewElite);

		}
		//cout<<"-------------Fim-New Go---------------"<<endl;
	}
	/*
	for(vector<Solution>::iterator it=GenerateNewElite.begin(); it!=GenerateNewElite.end(); ++it){
			cout<<*it<<endl;
	}
	*/
	double cost=0;

	int index = getBestPRSol(GenerateNewElite,cost);
	/*cout<<"-----------------------------"<<endl;
	cout<<GenerateNewElite.at(index)<<" - Valor: "<<GenerateNewElite.at(index).get_cost()<<endl;
	cout<<"-----------------------------"<<endl;*/

	for(auto it = GenerateNewElite.at(index).get_param().begin(); it!=GenerateNewElite.at(index).get_param().end(); ++it){
		BestSol->add_param(*it);
	}
	BestSol->set_cost(cost);
	/*cout<<"-----------------------------"<<endl;
	cout<<"Before Return: "<<*BestSol<<endl;
	cout<<"-----------------------------"<<endl;
	cout<<"SIZE: "<<GenerateNewElite.size()<<endl;*/

	return BestSol;
}

int PathRelinking::getBestPRSol(vector<Solution>& lista, double& cost){
		int index,cont=0;;
		for(vector<Solution>::iterator it = lista.begin(); it!=lista.end(); ++it){
			if(it == lista.begin()) {index = 0; cost = lista[index].get_cost();}
			if(lista[index].get_cost()<it->get_cost()){
						index = cont;
						cost = it->get_cost();
			}
			++cont;
		}


		return index;
}

int PathRelinking::GenPath(Solution Guide, Solution Arrive, vector<Solution> &GenerateNewElite, int index, int size){
	static double cost;
	if(index<size-1){
		if(Guide.get_param()[index] != Arrive.get_param()[index]){
			//cout<<"-----------------------------"<<endl;
			/*cout<<Guide<<endl;*/
			Guide.change_param(Arrive.get_param()[index], index);
			double * param = new double [size];
			for(int i = 0; i<size; ++i){
				param[i] = Guide.get_param()[i];
			}
			if(NotinTheSet(Guide,GenerateNewElite)){
				//cout << "***Chamei a rede neural via path_relinking" << endl;
				cost = evaluate(param);
				Guide.set_cost(cost);
			//	cout<<Guide<<endl;
				/*cout<<"Valor: "<<Guide.get_cost()<<endl;
				cout<<Arrive<<endl;*/
			//	cout<<"-----------------------------"<<endl;
				GenerateNewElite.push_back(Guide);
			}
			delete[] param;
			++index;
			return GenPath(Guide, Arrive, GenerateNewElite, index, size);
		}else{
			++index;
			return GenPath(Guide, Arrive, GenerateNewElite, index, size);
		}
	}

	return 0;
}

bool PathRelinking::NotinTheSet(Solution& Sol, vector<Solution> &GenerateNewElite){
	vector<Solution> teste = GenerateNewElite;
	Solution s = Sol;
	for(vector<Solution>::iterator it = teste.begin();it != teste.end(); it++){
		if(is_equal(s,*it)) return false;
	}
	return true;
}

double PathRelinking::evaluate(double* param, int size){
		ostringstream buffer;
		buffer.str("");
		cout<<"### Chamei a Rede Neural no PR!"<<endl;
		buffer	<< "python ./src/python/neural_network.py fashion"
				<< " "	<< param[0]
				<< " "	<< param[1]
				<< " "	<< param[2]
				<< " "	<< param[3]
				<< " "	<< param[4]
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


		return solution;
		//return (param[0]+param[1]-param[2]+(param[3]*1000) * (param[4]*100000));
}

#endif // PATH_RELINKING_CPP_
