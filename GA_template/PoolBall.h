#pragma once
#include <ostream>
using namespace std;
#include <vector>
#include <cmath>  
#define CHROM_SIZE 15
class PoolBall
{
public:
	vector<double> genes;
	double fitness;
public:
	PoolBall();
	~PoolBall();
	void Mutate(double prob);
	void UpdateFitness();
	bool Criteria();
	friend ostream& operator << (ostream& os, PoolBall& p) {
		// This is where you define the overloaded output operation
		// for this particular genome.  Need to print the entire genome
		os << "(" << p.genes[0];
		for (int i = 1; i < CHROM_SIZE; i++)
		{
			os << "," << p.genes[i];
		} 
		os<< ")";
		return os;// enables cascading
	}
};
void Crossover(PoolBall genome1, PoolBall genome2, PoolBall &genome3, PoolBall &genome4);
