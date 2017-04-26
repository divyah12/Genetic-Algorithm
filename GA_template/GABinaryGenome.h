#pragma once
#include <bitset>
#include <iostream>
using namespace std;
#define CHROM_SIZE 20
class GABinaryGenome
{
public:
	bitset<CHROM_SIZE> bits;
	double fitness;
public:
	GABinaryGenome();
	~GABinaryGenome();
	void Mutate(double prob);
	void UpdateFitness();
	bool Criteria();
	friend ostream& operator << (ostream& os, GABinaryGenome& p) {
		// This is where you define the overloaded output operation
		// for this particular genome
		os << p.bits;
		return os;// enables cascading
	}
	
};
void Crossover(GABinaryGenome genome1, GABinaryGenome genome2, GABinaryGenome &genome3, GABinaryGenome &genome4);
// Need an overloaded << here for this genome.

