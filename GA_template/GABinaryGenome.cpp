#include "GABinaryGenome.h"
// the default returns a random genome

//////////////////////////////////////////////////////////////////////
//This function (not a method) performs the crossover operation on the two individuals
// in the population. It presently performs
// a single point crossover on to bitset chromosomes. 
// NOTE:
//////////////////////////////////////////////////////////////////////
void Crossover(GABinaryGenome genome1, GABinaryGenome genome2, GABinaryGenome &genome3, GABinaryGenome &genome4 )
{
	// Do a single point chrossover so pick a position pos to split at
	int pos = rand() % (CHROM_SIZE - 1);// Returns a number from 0 to CHROM_SIZE -2 
										//	cout << pos << endl;
										// We will cut the chrom after this index !  IE we will not do a cut at either end
										//  This is so there will be an actual modification cut
	for (int i = 0; i < CHROM_SIZE; i++) {
		if (i <= pos) {//first section
			genome3.bits[i] = genome1.bits[i];
			genome4.bits[i] = genome2.bits[i];
		}
		else { //second section
			genome3.bits[i] = genome2.bits[i];
			genome4.bits[i] = genome1.bits[i];
		}

	}
	//cout << genome1.bits << endl;
	//cout << genome2.bits<<endl;
	//cout << pos << endl;
	//cout << genome3.bits<<endl;
	//cout << genome4.bits<<endl;
	//cout << "------------------------" << endl;


}
GABinaryGenome::GABinaryGenome()
{
	for (int i = 0; i < bits.size(); i++)
		bits[i] = rand() % 2; 
}


GABinaryGenome::~GABinaryGenome()
{
}

bool GABinaryGenome::Criteria()
{
	if (fitness == CHROM_SIZE)return true;
	return false;

}

void GABinaryGenome::UpdateFitness()
{
    fitness = 0.0;
	for (int i = 0; i < CHROM_SIZE; i++)
		fitness += bits[i];
	// or we could do the following
	// fitness = bits.count();
}
/////////////////////////////////////////////////////////////////
// This will mutate the chromosome in situ with probabilite prop
// it will do this test for each bit.  This version
// looks at each bit and mutates it based on prob.
////////////////////////////////////////////////////////////////
void GABinaryGenome::Mutate(double prob)
{
	for (int i = 0; i < CHROM_SIZE; i++) {
		if (rand() / (double)RAND_MAX < prob) {
			bits[i] = (bits[i] == 1) ? 0 : 1;
		}
	}
	UpdateFitness();
}
