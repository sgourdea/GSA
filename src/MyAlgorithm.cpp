
#include "MyAlgorithm.h"

MyAlgorithm::MyAlgorithm(const Problem &pbm, const SetUpParams &setup):
		_setup{setup},
		_g{_g_const},
		_mutationProbability{0.1},
		_crossoverProbability{0.5}
{
	_solutions.reserve(_setup.population_size());
	for (int i = 0; i < _setup.population_size(); ++i) {
		Solution *s = new Solution(pbm);
		_solutions[i] = s;
	}
}

MyAlgorithm::~MyAlgorithm() {
	for (int i = 0; i < _setup.population_size(); ++i)
		delete _solutions[i];
}

/* ToFix
std::ostream& MyAlgorithm::operator<< (std::ostream& os, const MyAlgorithm& myAlgo) {
	//toDo
	return os;
}

std::istream& MyAlgorithm::operator>> (std::istream& is, MyAlgorithm& myAlgo) {
	//toDo
	return is;
}

MyAlgorithm& MyAlgorithm::operator= (const MyAlgorithm& myAlgo) {
	//toDo
	return myAlgo;
}
*/

const SetUpParams& MyAlgorithm::setup() const {
	return _setup;
}

void MyAlgorithm::initialize()
{
	for (int i = 0; i < _setup.population_size(); ++i)
        _solutions[i]->initialize();
}

void MyAlgorithm::evaluate() {
	_fitness_values.reserve(_setup.population_size());
	for (int i = 0; i < _setup.population_size(); ++i) {
		_fitness_values[i].fitness = _solutions[i]->fitness();
		_fitness_values[i].index = i;
	}

	_upper_cost = 0;
	_lower_cost = _setup.population_size() - 1;
}

const std::vector<Solution*>& MyAlgorithm::solutions() const {
	return _solutions;
}

unsigned int MyAlgorithm::upper_cost() const {
	return _upper_cost;
}
		
unsigned int MyAlgorithm::lower_cost() const {
	return _lower_cost;
}

Solution& MyAlgorithm::solution(const unsigned int index) const {
	return *_solutions[index];
}
        
std::vector<struct particle>&  MyAlgorithm::fitness_values() {
	return _fitness_values;
}

double MyAlgorithm::fitness(const unsigned int index) const {
	return _solutions[index]->fitness(); //Pas sûr si on regarde l'index du tableau _fitness_values ou l'index du .index du struct
}

double MyAlgorithm::best_mass() const {
	return _fitness_values[_upper_cost].fitness;
}
		
double MyAlgorithm::worst_mass() const {
	return _fitness_values[_lower_cost].fitness;
}

Solution& MyAlgorithm::best_solution() const {
	return *_solutions[_upper_cost];
}

Solution& MyAlgorithm::worst_solution() const {
	return *_solutions[_lower_cost];
}

void MyAlgorithm::evolution(int iter) {
	//Récupération de la meilleure fitness pour cette itération
	//IL FAUT CORRIGER UPPER/LOWER COST JE COMPRENDS PAS

	//Constante G
	double g = MyAlgorithm::g_const(iter, _setup.nb_evolution_steps());

    

	//https://fr.mathworks.com/matlabcentral/fileexchange/27756-gravitational-search-algorithm--gsa-/content/Gravitational%20Search%20algorithm/GSA.m
}

void MyAlgorithm::main() {
    double moy_best_fit=0.0;
	for(int runs=0 ; runs < _setup.independent_runs() ; runs++)
	{
		initialize();
		for(int iter=0 ; iter < _setup.nb_evolution_steps() ; iter++)
		{
			evolution(iter);
		}
		evaluate();
		moy_best_fit+= 0//meilleure fitness de la solution (me souvient plus de la formule);
	}
    moy_best_fit/=_setup.independent_runs();
    std::cout<<"Moyenne : "<<moy_best_fit<<std::endl;
    //Affichage de la moyenne des meilleures fitness.
}

double MyAlgorithm::g_const(int iter, int max_iter) const {
	double _g_const = 100;
	int alpha = 20;
	return _g_const * exp(-alpha * (iter / max_iter));
}