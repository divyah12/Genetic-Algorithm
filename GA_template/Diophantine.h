#pragma once
#include <ostream>
using namespace std;
#include <vector>
#include <cmath>
#define CHROM_SIZE 4
class diophantine
{
public:
	vector<double> genes;
	double fitness;
public:
	diophantine();
	~diophantine();
	void Mutate(double prob);
	void UpdateFitness();
	bool Criteria(); // Define the return criteria
	friend ostream& operator << (ostream& os, diophantine& p) {
		// This is where you define the overloaded output operation
		// for this particular genome
		os << "(" << p.genes[0] 
			<< "," << p.genes[1] 
			<< "," << p.genes[2]
			<<"," << p.genes[3]<<")";
		return os;// enables cascading
	}
};
void Crossover(diophantine genome1, diophantine genome2, diophantine &genome3, diophantine &genome4);
//Need an overloaded << output here.