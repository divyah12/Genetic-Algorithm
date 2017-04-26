#pragma once
#include<vector>
#include <bitset>
#include <iostream>
using namespace std;
#define CHROM_SIZE 16
#define setsum 321
class GASetGenome
{
public:
	bitset<CHROM_SIZE> bits;
	vector<int> setval;
	double fitness;
public:
	GASetGenome();
	~GASetGenome();
	void Mutate(double prob);
	void UpdateFitness();
	bool Criteria();
	friend ostream& operator << (ostream& os, GASetGenome& p) {
		// This is where you define the overloaded output operation
		// for this particular genome
		os << p.bits;
		return os;// enables cascading
	}

};
void Crossover(GASetGenome genome1, GASetGenome genome2, GASetGenome &genome3, GASetGenome &genome4);
// Need an overloaded << here for this genome.

