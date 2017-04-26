#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Population.h"
template<typename genomeType>
class GASimpleGA
{
	int popSize;// size of population
	int maxGen;// max number of generations allowed to run
	int gen; // Holds present generation of the ga
	double pCross;// probability of crossover 
	double pMut;// probability of mutation
	bool elitism;
	Population<genomeType> population;
	SelectionType selType;
public:
	GASimpleGA();
	~GASimpleGA();
	void populationSize(int);//sets the population size
	void nGenerations(int);// sets the maximum number of generations
	void pMutation(double pMut);// sets the probability of mutation
	void pCrossover(double pCross);// sets the probability of crossover
	string statistics(StatRequest);// used to display the statistics. Returns a string
	int Generation();
	void evolve();
	void Elitism(bool e);
	void Selection(SelectionType stype);
	
};


// Simple ga constructor
template<typename genomeType>
GASimpleGA<genomeType>::GASimpleGA()
	: popSize(10)// default initialization for size
	, maxGen(100)// default initialization for number of generations
	, elitism(false)
{
}

template<typename genomeType>
GASimpleGA<genomeType>::~GASimpleGA()
{
}
template<typename genomeType>
void GASimpleGA<genomeType>::Selection(SelectionType stype)
{
	selType = stype;
}
// Sets the population size for the algorithm
template<typename genomeType>
void GASimpleGA<genomeType>::populationSize(int sz)
{
	popSize = sz;
}

// sets the maximum number of generations that will be allowed to run
template<typename genomeType>
void GASimpleGA<genomeType>::nGenerations(int ngen)
{
	maxGen = ngen;
}

template<typename genomeType>
void GASimpleGA<genomeType>::pMutation(double p)
{
	pMut = p;
}

template<typename genomeType>
void GASimpleGA<genomeType>::pCrossover(double p)
{
	pCross = p;
}

// Returns the collected stats for the ga
template<typename genomeType>
string GASimpleGA<genomeType>::statistics(StatRequest sr)
{
	return population.GetStats(sr);
}

// This function will run the GA until the maximum number of generations
// is completed or stop early if a defined criteria is met.
template<typename genomeType>
void GASimpleGA<genomeType>::evolve()
{
	genomeType genome1, genome2, genome3, genome4;
	population.SetElitism(elitism);
	population.GeneratePopulation(popSize);
	if (selType == RANK)population.PopulationSort();
	population.UpdateStats();

	gen = 0;
	while (gen < maxGen) {
		Population<genomeType> NewPop(popSize);// create the new population
		NewPop.SetElitism(elitism);
		int NewPopSize = 0;
		if (elitism) {
			// Add the top  genome to twice to this new population
			NewPop.InsertGenome(population.BestGenome());//Insert the best one
			NewPop.InsertGenome(population.BestGenome());
			NewPopSize += 2;
		}
		while (NewPopSize < popSize) {
			genome1 = population.Selection(selType);
			genome2 = population.Selection(selType);
			if ((rand() / (double)RAND_MAX) < pCross) {
				Crossover(genome1, genome2, genome3, genome4);
				genome3.Mutate(pMut);
				genome4.Mutate(pMut);
				NewPop.InsertGenome(genome3);
				NewPop.InsertGenome(genome4);
				NewPopSize += 2;
			}
			else {
				NewPop.InsertGenome(genome1);
				NewPop.InsertGenome(genome2);
				NewPopSize += 2;
			}
		}
		population = NewPop;
		if(selType== RANK) population.PopulationSort();
		population.UpdateStats();
		if (population.CriteriaMet())break;
		cout << "Average  fitness in " << gen << " : " << population.AveFitness() << endl;
		gen++;
	}
	//Pop.Dump(gen, true);
}

template<typename genomeType>
void GASimpleGA<genomeType>::Elitism(bool e)
{
	elitism = e;
}
template<typename genomeType>
int GASimpleGA<genomeType>::Generation()
{
	return gen;
}