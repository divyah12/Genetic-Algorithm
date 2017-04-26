#include<iostream>
#include <stdlib.h> 
#include<fstream>
#include<vector>
#include<bitset>
#include<time.h>
#include<algorithm>

#define gasize 50
#define bitsize 20
#define pmut 0.01
#define pcross 0.8
#define endl '\n'
using namespace std;
ofstream mycout("example.txt");
double maxfitness = 0;
bitset<bitsize> maxgene;

bitset<bitsize> selection(vector< pair < double, bitset<bitsize> >>pool,double sumfitness) {
	//pool
	double val =sumfitness*( rand() /(double)RAND_MAX);
	double travesesum = pool[0].first;
		for (vector< pair < double, bitset<bitsize> >>::iterator it = pool.begin(); it != pool.end(); ++it) {
			travesesum += it->first;
			mycout << "val  " << val << "selection sum   " << travesesum << endl;
			if (travesesum>val)
			{
mycout << it->second << "   selected chromo" << endl;
				return it->second;
			}
		}
	return NULL;
}
bitset<bitsize> fillchrom() 
{
	bitset<bitsize> x;
	for (int i = 0; i < bitsize; i++)
	{
		x[i] = rand() % 2;
	}
	return x;
}
//fills the 1st generation chrom pool
vector< pair < double, bitset<bitsize> >> initial_population(vector< pair < double, bitset<bitsize> >>pool,double &sumfitness) {
	for (int i = 0;i < gasize;i++) {
		bitset<bitsize> x = fillchrom();
		double temp = x.count();
		if (temp > maxfitness) { 
			maxfitness = temp; 
			maxgene = x;
		}
		sumfitness += temp;
		pool.push_back(make_pair(temp,x));
mycout << "inipoplu--" <<temp<<"\t"<<x<< endl;
	}
mycout <<"sumfit "<< sumfitness << "\t maxfit " << maxfitness << endl;
	return pool;
}
void crossover(bitset<bitsize> &chromX, bitset<bitsize> &chromY) {
		int cross_point = rand() % (bitsize-1);
		string temp1 = chromX.to_string();
		string temp2 = chromY.to_string();
		string t1 = temp1.substr(0, cross_point) + temp2.substr(cross_point, bitsize);
		string t2 = temp2.substr(0, cross_point) + temp1.substr(cross_point, bitsize);

		chromX = (bitset<bitsize>)t1; chromY = (bitset<bitsize>)t2;
	
}

void mutation(bitset<bitsize> &offspring) {
	for (int i = 0; i<bitsize; i++)
	{
		if ((rand() / (double)RAND_MAX) < pmut)
			offspring.flip(i);
	}
}

int main() {
	srand(5);
	int it = 0;
	double sumfitness = 0.0;
	vector< pair < double, bitset<bitsize> >> pool;
	pool=initial_population(pool,sumfitness);
	while (it < 1000 && maxfitness < bitsize) {
mycout << "---------------" << it << "----------------" << maxfitness <<"--------------"<<sumfitness<< endl;
		vector< pair < double, bitset<bitsize> >> newpool;
		int newsumfitness = 0;
		//operation saved to new chrom pool
		while (newpool.size()<50) {
			
			bitset<bitsize>chromX = selection(pool,sumfitness);
			bitset<bitsize>chromY = selection(pool,sumfitness);
			if( (rand() / (double)RAND_MAX) < pcross) {
				mycout << "pcross" << endl;

				crossover(chromX, chromY);

				newpool.push_back(make_pair(chromX.count(), chromX));
				newsumfitness = newsumfitness + chromX.count();
				if (chromX.count() > maxfitness) { 
					maxfitness = chromX.count();
					maxgene = chromX;
				}
				mycout << chromX.count() << "\t" << chromX << endl;

				newpool.push_back(make_pair(chromY.count(), chromY));
				newsumfitness = newsumfitness + chromY.count();
				if (chromY.count() > maxfitness) {
					maxfitness = chromY.count();
					maxgene = chromY;
				}
				mycout << chromY.count() << "\t" << chromY << endl;

				mutation(chromX);
				newpool.push_back(make_pair(chromX.count(), chromX));
				newsumfitness = newsumfitness + chromX.count();
				if (chromX.count() > maxfitness) {
					maxfitness = chromX.count();
					maxgene = chromX;
				}
				mycout << chromX.count() << "\t" << chromX << endl;

				mutation(chromY);
				newpool.push_back(make_pair(chromY.count(), chromY));
				newsumfitness = newsumfitness + chromY.count();
				if (chromY.count() > maxfitness) {
					maxfitness = chromY.count();
					maxgene = chromY;
				}
				mycout << chromY.count() << "\t" << chromY << endl;
			}
			else
			{
				newpool.push_back(make_pair(chromX.count(), chromX));
				newsumfitness = newsumfitness + chromX.count();
				if (chromX.count() > maxfitness) {
					maxfitness = chromX.count();
					maxgene = chromX;
				}
				mycout << chromX.count() << "\t" << chromX << endl;

				newpool.push_back(make_pair(chromY.count(), chromY));
				newsumfitness = newsumfitness + chromY.count();
				if (chromY.count() > maxfitness) {
					maxfitness = chromY.count();
					maxgene = chromY;
				}
				mycout << chromY.count() << "\t" << chromY << endl;

			}
		}
		cout << "Generation: " << it << "\tmaxfitness" << maxfitness << "\tsumfitness" << (double)(sumfitness/(double)50) << endl;
	//	cout << "gene : " << maxgene << endl;

		mycout << "fitness sum----" << newsumfitness << endl;
		sumfitness = newsumfitness;
		pool.clear();
		pool = newpool;
		newpool.clear();
		//newpool given to pool 
		it++;
	}
	
	mycout.close();
	return 0;
}

