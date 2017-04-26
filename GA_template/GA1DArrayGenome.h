#pragma once
#pragma once
#include <ostream>
using namespace std;
#include <vector>
#include <cmath>
#define CHROM_SIZE 2
class GA1DArrayGenome
{
public:
	vector<double> genes;
	double fitness; 
public:
	GA1DArrayGenome();
	~GA1DArrayGenome();
	void Mutate(double prob);
	void UpdateFitness();
	bool Criteria();
	friend ostream& operator << (ostream& os, GA1DArrayGenome& p) {
		// This is where you define the overloaded output operation
		// for this particular genome
		os << "(" << p.genes[0] << "," << p.genes[1] << ")";
		return os;// enables cascading
	}
};
void Crossover(GA1DArrayGenome genome1, GA1DArrayGenome genome2, GA1DArrayGenome &genome3, GA1DArrayGenome &genome4);
//Need an overloaded << output here.