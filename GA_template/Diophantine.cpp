#include "diophantine.h"
// the default returns a random genome
// 
//////////////////////////////////////////////////////////////////////
//This function (not a method) performs the crossover operation on the two individuals
// in the population. It presently performs
// a single point crossover on to bitset chromosomes. 
// NOTE: You send in parents and get back children.
//////////////////////////////////////////////////////////////////////
void Crossover(diophantine genome1, diophantine genome2, diophantine &genome3, diophantine &genome4)
{
	// Do a single point chrossover so pick a position pos to split at
	int pos = rand() % (CHROM_SIZE - 1);// Returns a number from 0 to CHROM_SIZE -2 
										//	cout << pos << endl;
										// We will cut the chrom after this index !  IE we will not do a cut at either end
										//  This is so there will be an actual modification cut
	for (int i = 0; i < CHROM_SIZE; i++) {
		if (i <= pos) {//first section
			genome3.genes[i] = genome1.genes[i];
			genome4.genes[i] = genome2.genes[i];
		}
		else { //second section
			genome3.genes[i] = genome2.genes[i];
			genome4.genes[i] = genome1.genes[i];
		}

	}
	genome3.UpdateFitness();
	genome4.UpdateFitness();
}

//This is the default constructor.  It generates a random chromosome
diophantine::diophantine()
{
	//The range of possible x and y values for this genome is from -5 to 5
	for (unsigned int i = 0; i < CHROM_SIZE; i++)
		genes.push_back(rand()%30+1);
	UpdateFitness();
}

// Not needed 
diophantine::~diophantine()
{
}

bool diophantine::Criteria()
{
	if (fitness == 1.0)return true;
	return false;
}
////////////////////////////////////////////////////////////////////////
// Note that for this particular function there are two possibile results. 
// one is near (0,0) which is suboptimal
// and one near (1.697,1.697) which is near optimal
// Sometimes the ga will get hung up on the suboptimal one
// See if you can get it to occur.
// This applies the fitness function to the genome and
// sets its fitness value.
////////////////////////////////////////////////////////////////////////
void diophantine::UpdateFitness()
{
	int f = abs(genes[0] + 2 * genes[1] + 3 * genes[2] + 4 * genes[3] - 30);
	fitness = 1.0 / (1.0 + f);
}
/////////////////////////////////////////////////////////////////
// This will mutate the chromosome in situ with probabilite prop
// it will do this test for each bit.  This version
// looks at each bit and mutates it based on prob.
////////////////////////////////////////////////////////////////
void diophantine::Mutate(double prob)
{
	int v;
	int  mut_range = 7;// from -3 to + 3,  Must be odd
	for (int i = 0; i < CHROM_SIZE; i++) {
		if (rand() / (double)RAND_MAX < prob) {
			v = rand() % (mut_range)-(mut_range-1)/2;
			genes[i] = ((genes[i] + v) < 1 || (genes[i] + v) > 30) ? genes[i] : genes[i] + v;
		}
	}
	UpdateFitness();
}

