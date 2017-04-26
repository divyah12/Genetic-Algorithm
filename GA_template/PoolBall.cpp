#include "PoolBall.h"
#include<iostream>
#include "PoolBall.h"
// the default returns a random genome
// 
//////////////////////////////////////////////////////////////////////
//This function (not a method) performs the crossover operation on the two individuals
// in the population. It presently performs
// a single point crossover on to bitset chromosomes. 
// NOTE: You send in parents and get back children.
//////////////////////////////////////////////////////////////////////
void Crossover(PoolBall genome1, PoolBall genome2, PoolBall &genome3, PoolBall &genome4)
{
	//std::cout << genome3.genes.size() << endl;
	//This is where you write the order crossover operation
	vector<double> temp1, temp2, temp;
	int pos1 = rand() % (CHROM_SIZE - 1);// Returns a number from 0 to CHROM_SIZE -2 
	int pos2 = rand() % (CHROM_SIZE - 1);//	cout << pos << endl;
										 //  This is so there will be an actual modification cut
										 // We will cut the chrom after this index !  IE we will not do a cut at either end
	if (pos1 > pos2) 		swap(pos1, pos2);
	//genome3
	//copy subset 
	for (int i = pos1; i < pos2; i++) {
		genome3.genes[i] = genome1.genes[i];
		temp.push_back(genome1.genes[i]);
	}
	temp1 = genome2.genes;//copy of 2nd parent
	
	vector<double>::iterator it;
	//temp holds the subsequence
	//following removes the temp in temp1
	while (!temp.empty()) {
	//	cout << "backval" << temp.back() << endl;
		it = find(temp1.begin(), temp1.end(), temp.back());
		it++;
		int pos = distance(temp1.begin(), it);
		//cout << "pos  " << pos << endl;
		//cout << temp1.begin() + pos << endl;
		temp1.erase(temp1.begin() + pos - 1);
		temp.pop_back();
	}
	//now temp1 contains only the values which are not in the subsequence
	for (int i = 0; i < pos1; i++)
	{
		genome3.genes[i] = temp1[i];
	}
	int j = pos1;
	for (int i = pos2; i < CHROM_SIZE; i++)
	{
		genome3.genes[i] = temp1[j++];
	}//copy to genome3
//genome4
//copy subset 
	for (int i = pos1; i < pos2; i++) {
		genome4.genes[i] = genome2.genes[i];
		temp.push_back(genome2.genes[i]);
	}
	temp1 = genome1.genes;//copy of 2nd parent
	//temp holds the subsequence
	//following removes the temp in temp1
	while (!temp.empty()) {
		it = find(temp1.begin(), temp1.end(), temp.back());
		it++;
		int pos = distance(temp1.begin(), it);
		temp1.erase(temp1.begin() + pos-1);
		temp.pop_back();
	}
	//now temp1 contains only the values which are not in the subsequence
	for (int i = 0; i < pos1; i++)
	{
		genome4.genes[i] = temp1[i];
	}
	j = pos1;
	for (int i = pos2; i < CHROM_SIZE; i++)
	{
		genome4.genes[i] = temp1[j++];
	}//copy to genome4
	
}

//This is the default constructor.  It generates a random chromosome
PoolBall::PoolBall()
{
	genes = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	//Here is where you write the code to generate a random permutation
	int n = 0;
	
	while(n < CHROM_SIZE)
	{
		int j = rand() % CHROM_SIZE + n;
			if (j <CHROM_SIZE) {
				int c = genes[j];
				genes[j] = genes[n];
				genes[n] = c;
				n++;
			}
	}

	// call this last
	UpdateFitness();
}

// Not needed 
PoolBall::~PoolBall()
{
}
////////////////////////////////////////////////////////////////////////
// update the fitness value for this chromosome
////////////////////////////////////////////////////////////////////////
void PoolBall::UpdateFitness()
{
// here is where you write the code to calculate the fitness of this genome
	int fit = 0;
	if (abs(genes[1] - genes[2]) == genes[0]) fit++;
	if (abs(genes[3] - genes[4]) == genes[1]) fit++;
	if (abs(genes[4] - genes[5]) == genes[2]) fit++;
	if (abs(genes[6] - genes[7]) == genes[3]) fit++;
	if (abs(genes[7] - genes[8]) == genes[4]) fit++;
	if (abs(genes[8] - genes[9]) == genes[5]) fit++;
	if (abs(genes[10] - genes[11]) == genes[6]) fit++;
	if (abs(genes[11] - genes[12]) == genes[7]) fit++;
	if (abs(genes[12] - genes[13]) == genes[8]) fit++;
	if (abs(genes[13] - genes[14]) == genes[9]) fit++;
	
	fitness = 1.0 / (1.0 + abs(fit-10));
}

bool PoolBall::Criteria()
{
	// return true if the fitness is optimal(if you know it)

	if(fitness==1.0)return true;//This is just temp for compilation
	return false;
}
/////////////////////////////////////////////////////////////////
// This will mutate the chromosome in situ with probabilite prop
// Implement a permutation mutation here
////////////////////////////////////////////////////////////////
void PoolBall::Mutate(double prob)
{// just do a random swap with probability prob
	for (int i = 0; i < CHROM_SIZE; i++) {
		int pos1 = rand() % (CHROM_SIZE - 1);// Returns a number from 0 to CHROM_SIZE -2 
		int pos2 = rand() % (CHROM_SIZE - 1);
		if (rand() / (double)RAND_MAX < prob) {
			double temp = genes[pos1];
			genes[pos1] = genes[pos2];
			genes[pos2] = temp;
		}
	}
	UpdateFitness();
}
