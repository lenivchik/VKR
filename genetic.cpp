#include "genetic.h"

Genetic::Genetic() {
	Ex = new example();
	Best.fitness = 100;
}

int Genetic::Solve() {
	int fitness = -1;
	double oldbest = 100;
	int sameiter = 0;
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAXPOP; i++) {
		for (int j = 0; j < MASLEN; j++) {
			population[i].alleles[j] = rand() % (2);
		}
	}

	if (fitness = CreateFitnesses(Best)) {
		return fitness;
	}
	while (Best.fitness == 100) {
		for (int i = 0; i < MAXPOP; i++) {
			for (int j = 0; j < MASLEN; j++) {
				population[i].alleles[j] = rand() % (2);
			}
		}
		CreateFitnesses(Best);
	}
	int iterations = 0;
	while (fitness >= 1 || iterations < 50000) {
		if (Best.fitness < oldbest) {
			oldbest = Best.fitness;
			sameiter = 0;
		}
		else {
			sameiter += 1;
			if (sameiter > 50) {
				GenerateRand();
				sameiter = 0;
			}
		}
		if (iterations % 1000 == 0)
			cout << "\nwait " << "\n";

		GenerateLikelihoods();
		CreateNewPopulation();
		if (fitness = CreateFitnesses(Best)) {
			printf("%d\n", iterations);

			return fitness;
		}
		iterations++;
	}
	printf("%d\n", iterations);
	return 1;
}

int Genetic::Fitness(gene& gn, gene& Best) {
	if ((BinToDec(gn.alleles, 5) > 0.3) || (FindMax(gn.alleles, 1) > 0.3) || (BinToDec(gn.alleles, 9) > 0.3) || (BinToDec(gn.alleles, 0) > BinToDec(gn.alleles, 4)) || (BinToDec(gn.alleles, 0) == 0) || (BinToDec(gn.alleles, 5) == 0) || (BinToDec(gn.alleles, 5) > BinToDec(gn.alleles, 9))) {
		if (FindMax(gn.alleles, 1) > 0.3)
			return gn.fitness = 100;
		while ((BinToDec(gn.alleles, 5) > BinToDec(gn.alleles, 9))) {
			for (int i = 0; i < 15; i++) {
				gn.alleles[25 + i] = rand() % (2);
				gn.alleles[85 + i] = rand() % (2);
			}
		}
		while ((BinToDec(gn.alleles, 0) > BinToDec(gn.alleles, 4))) {
			for (int i = 0; i < 5; i++) {
				gn.alleles[0 + i] = rand() % (2);
				gn.alleles[20 + i] = rand() % (2);
			}
		}

	}
	functions* c = new functions(BinToDec(gn.alleles, 0), FindMin(gn.alleles, 0), FindMid(gn.alleles, 0), FindMax(gn.alleles, 0), BinToDec(gn.alleles, 4), BinToDec(gn.alleles, 5), FindMin(gn.alleles, 1), FindMid(gn.alleles, 1), FindMax(gn.alleles, 1), BinToDec(gn.alleles, 9));
	double total1 = 0, total2 = 0, total3 = 0, len = Ex->getLen();
	for (int i = 0; i < len; i++) {
		rule* rule = Ex->getRule(i);
		total1 = c->check(rule->getFirst(), rule->getSecond());
		total2 += pow((rule->getResult() - total1), 2);
	}
	double total = sqrt(total2) / len;

	if (total < Best.fitness) {
		Best.fitness = total;
		for (int i = 0; i < MASLEN; i++)
			Best.alleles[i] = gn.alleles[i];
	}
	delete c;
	return gn.fitness = total;
}

int Genetic::CreateFitnesses(gene& Best) {
	float avgfit = 0;
	int fitness = 0;
	for (int i = 0; i < MAXPOP; i++) {
		fitness = Fitness(population[i], Best);
		avgfit += fitness;
		if (fitness < 1) {
			return i;
		}
	}

	return 0;
}

float Genetic::MultInv() {
	float sum = 0;

	for (int i = 0; i < MAXPOP; i++) {
		sum += 1 / ((float)population[i].fitness);
	}

	return sum;
}

void Genetic::GenerateLikelihoods() {
	float multinv = MultInv();
	float last = 0;
	for (int i = 0; i < MAXPOP; i++) {
		population[i].likelihood = last = last + ((1 / ((float)population[i].fitness) / multinv) * 100);
	}
}

int Genetic::GetIndex(float val) {
	float last = 0;
	for (int i = 0; i < MAXPOP; i++) {
		if (last <= val && val <= population[i].likelihood) return i;
		else last = population[i].likelihood;
	}
	return MAXPOP;
}

gene Genetic::Breed(int p1, int p2) {
	int crossover = rand() % MASLEN + 1;
	int first = rand() % 100;

	gene child = population[p1];

	int initial = 0, final = MASLEN - 1;
	if (first < 50) initial = crossover;
	else final = crossover + 1;

	for (int i = initial; i < final; i++) {
		child.alleles[i] = population[p2].alleles[i];
		if (rand() % 3000 < 10) {
			child.alleles[i] = (child.alleles[i] == 0) ? 1 : 0;
		}
	}

	return child;
}

void Genetic::CreateNewPopulation() {
	gene temppop[MAXPOP];

	for (int i = 0; i < MAXPOP; i++) {
		int parent1 = 0, parent2 = 0, iterations = 0;
		while (parent1 == parent2) {
			parent1 = GetIndex((float)(rand() % 101));
			parent2 = GetIndex((float)(rand() % 101));
			if (++iterations > 25) break;
		}

		temppop[i] = Breed(parent1, parent2);
	}

}

double Genetic::BinToDec(int* Array, int num) {
	double res = 0, k = 0;
	if (num < 5) {
		for (int i = num * 5; i < (num + 1) * 5; i++) {
			res += pow(2, 4 - k) * Array[i];
			k++;
		}
	}
	else {
		int decimal = 0;
		for (int i = ((num - 5) * 3 + 5) * 5; i < ((num - 5) * 3 + 8) * 5; i++) {
			decimal += pow(2, 15 - k) * Array[i];
			k++;
		}
		res = decimal * 0.3 / (pow(2, 15) - 1);
	}

	return res;
}


double Genetic::FindMin(int* Array, int num) {
	double min, x2, x3, fir, sec, th;
	if (!num) {
		fir = 1;
		sec = 2;
		th = 3;
	}
	else {
		fir = 6;
		sec = 7;
		th = 8;
	}
	min = BinToDec(Array, fir);
	x2 = BinToDec(Array, sec);
	x3 = BinToDec(Array, th);
	if (min > x2)
		min = x2;
	if (min > x3)
		min = x3;
	return min;
}

double Genetic::FindMax(int* Array, int num) {
	double max, x2, x3, fir, sec, th;
	if (!num) {
		fir = 1;
		sec = 2;
		th = 3;
	}
	else {
		fir = 6;
		sec = 7;
		th = 8;
	}
	max = BinToDec(Array, fir);
	x2 = BinToDec(Array, sec);
	x3 = BinToDec(Array, th);
	if (max < x2)
		max = x2;
	if (max < x3)
		max = x3;
	return max;
}
double Genetic::FindMid(int* Array, int num) {
	double x1, x2, x3, fir, sec, th;
	if (!num) {
		fir = 1;
		sec = 2;
		th = 3;
	}
	else {
		fir = 6;
		sec = 7;
		th = 8;
	}
	x1 = BinToDec(Array, fir);
	x2 = BinToDec(Array, sec);
	x3 = BinToDec(Array, th);
	if (x1 > x2 && x1 < x3 || x1 < x2 && x1 > x3)
		return x1;
	else
		if (x2 > x1 && x2 < x3 || x2 < x3 && x2 > x3)
			return x2;
		else
			return x3;
}

void Genetic::GenerateRand() {
	gene CURBest;
	CURBest.fitness = 100;
	while (CURBest.fitness == 100) {
		for (int i = 0; i < MAXPOP; i++) {
			for (int j = 0; j < MASLEN; j++) {
				population[i].alleles[j] = rand() % (2);
			}
		}
		CreateFitnesses(CURBest);
	}
}