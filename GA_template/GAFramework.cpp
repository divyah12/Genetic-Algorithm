// GAFramework.cpp : This is the basic framework for a Genetic Algorithm
// Programmed by Richard P. Simpson  1/6/2017
//
// We will start with this templated program and add new features to it.
// At the moment we have the following options defined in Population.h
//     Selection types ={TOURNAMENT, ROULETTE, RANK}
//     Statistic options = {ALL,BEST}
// In order to use this program for a new problem that has a new different chromosome 
// type you need to write a new class for your chromosome.  The two that comes with
// this initial version is "GABinaryGenome.h" and "GA1DArrayGenome.h".  You can use 
// these as examples of what you need to write.  
/////////////////////////////////////////////////////
#include <cmath>
#include "stdafx.h"
#include "GASimpleGA.h"
//#include "GASetGenome.h"
//#include "GABinaryGenome.h"
//#include "GA1DArrayGenome.h"
#include "PoolBall.h"
//#include "Diophantine.h"

int main()
{
	srand(8);// Change the 5 to get different random sequences generated.
	//Create a genetic algorithm using the GABinaryGenome type
	//GASimpleGA<GA1DArrayGenome> ga;// create a ga and tell it to use genome as it chromosome
	//GASimpleGA<GASetGenome> ga;
	//GASimpleGA<diophantine> ga; //Create a genetic algorithm called ga
	//GASimpleGA<GABinaryGenome> ga; //Create a genetic algorithm called ga
	GASimpleGA<PoolBall> ga; //Create a genetic algorithm called ga
	ga.populationSize(20);// Set population size to 20
	ga.nGenerations(1200);// stop running at the 1000'th generation
	ga.pCrossover(.8);// set probability of crossover
	ga.pMutation(.01);// set the probability of mutation
	ga.Elitism(true); // Turn on Elitism
	//ga.Selection(ROULETTE);// 
	//ga.Selection(RANK);
	ga.Selection(TOURNAMENT);
	// run the GA.
	// Note: at this point we have not stopping criteria.  How do we
	// add this and where? Think before you jump.
	ga.evolve();
    // Print the stats
	cout <<"GA stopped on generation "<< ga.Generation() << endl;
	// All is just one of the parameters that you can send into statistics()
	cout << ga.statistics(ALL) << endl;
	system("Pause");
	return 0;
}

