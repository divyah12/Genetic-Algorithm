#include "GA1DArrayGenome.h"
// the default returns a random genome
// 
//////////////////////////////////////////////////////////////////////
//This function (not a method) performs the crossover operation on the two individuals
// in the population. It presently performs
// a single point crossover on to bitset chromosomes. 
// NOTE: You send in parents and get back children.
//////////////////////////////////////////////////////////////////////
void Crossover(GA1DArrayGenome genome1, GA1DArrayGenome genome2, GA1DArrayGenome &genome3, GA1DArrayGenome &genome4)
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
GA1DArrayGenome::GA1DArrayGenome()
{
	//The range of possible x and y values for this genome is from -5 to 5
	for (unsigned int i = 0; i < CHROM_SIZE; i++)
		genes.push_back((rand()/(double)RAND_MAX)*10.0-5.0);
	UpdateFitness();
}

// Not needed 
GA1DArrayGenome::~GA1DArrayGenome()
{
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
void GA1DArrayGenome::UpdateFitness()
{
	double x=genes[0], y=genes[1];

	fitness = exp(-x*x + -y*y) + 2 * exp(-(x - 1.7)*(x - 1.7) - (y - 1.7)*(y - 1.7));
}

bool GA1DArrayGenome::Criteria()
{
	return false;  // no good criteria as of yet coded
}
/////////////////////////////////////////////////////////////////
// This will mutate the chromosome in situ with probabilite prop
// it will do this test for each bit.  This version
// looks at each bit and mutates it based on prob.
////////////////////////////////////////////////////////////////
void GA1DArrayGenome::Mutate(double prob)
{
	double variation;
	double mut_range = .2;// This certainly is dependent on the problem here
	for (int i = 0; i < CHROM_SIZE; i++) {
		if (rand() / (double)RAND_MAX < prob) {
			variation = (rand() / (double)RAND_MAX)*mut_range - mut_range / 2;
			genes[i] += variation;
		}
	}
	UpdateFitness();
}
