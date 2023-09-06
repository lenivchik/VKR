

#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "functions.h"
#include "example.h"

#define MAXPOP	30
#define MASLEN  (15*5+5*5)

struct gene {
	int alleles[MASLEN];
	double fitness;
	float likelihood;
};

class Genetic {
public:
	Genetic();
	int Solve();
	gene GetGene(int i) { return population[i]; }
	gene ReturnBest() {
		return Best;
	}

protected:
	int ca, cb, cc, cd;
	int result;
	gene population[MAXPOP];
	double BinToDec(int* Array, int num);
	int Fitness(gene&, gene&);
	void GenerateLikelihoods();	
	float MultInv();
	int CreateFitnesses(gene&);
	void CreateNewPopulation();
	void GenerateRand();
	int GetIndex(float val);
	example* Ex;
	gene Breed(int p1, int p2);
	gene Best;
	double FindMax(int*, int);
	double FindMid( int*, int);
	double FindMin( int*, int);
};
