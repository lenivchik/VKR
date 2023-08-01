#include <iostream>
#include "genetic.h"
using namespace std;

Genetic* Optimal = NULL;


double BinToDec(int* Array, int num) {
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

double FindMin(int* Array, int num) {
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

double FindMax(int* Array, int num) {
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
double FindMid(int* Array, int num) {
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
void Calculate3() {
	double a, b;
	printf("\nInput temperature difference: ");
	cin >> a;
	printf("\nInput rate of change: ");
	cin >> b;
	gene gn = Optimal->ReturnBest();
	functions* c = new functions(BinToDec(gn.alleles, 0), FindMin(gn.alleles, 0), FindMid(gn.alleles, 0), FindMax(gn.alleles, 0), BinToDec(gn.alleles, 4), BinToDec(gn.alleles, 5), FindMin(gn.alleles, 1), FindMid(gn.alleles, 1), FindMax(gn.alleles, 1), BinToDec(gn.alleles, 9));
	cout << "\nresult:" << c->check(a,b) << "\n";
	delete c;
	return;
}

void Calculate2() {
	example* Ex = new example();
	gene gn = Optimal->ReturnBest();
	functions* c = new functions(BinToDec(gn.alleles, 0), FindMin(gn.alleles, 0), FindMid(gn.alleles, 0), FindMax(gn.alleles, 0), BinToDec(gn.alleles, 4), BinToDec(gn.alleles, 5), FindMin(gn.alleles, 1), FindMid(gn.alleles, 1), FindMax(gn.alleles, 1), BinToDec(gn.alleles, 9));
	double total1 = 0, total2 = 0, total3 = 0, len = Ex->getLen();
	for (int i = 0; i < len; i++) {
		rule* rule = Ex->getRule(i);
		total1 = c->check(rule->getFirst(), rule->getSecond());
		total2 = rule->getResult() - total1;
		if (total2 > 0)
			total3 += (total2 / rule->getResult()) * 100;
		else
			total3 += (-1) * total2 / rule->getResult() * 100;
	}
	double total22 = total3 / len;
	//cout << "total " << total << "\n";
	/*cout << "fit " << total << "\n";*/
	delete c;
	cout << "Error " << total22 << "%\n";

}

void Calculate() {
	if (!Optimal) {
		Optimal = new Genetic();
		int ans;
		ans = Optimal->Solve();
		if (ans == -1) {
			cout << "No solution found." << endl;
		}
		else {
			gene gn = Optimal->ReturnBest();

			cout << "The solution is:\n";
			cout << "a = " << BinToDec(gn.alleles, 0) << "." << endl;
			cout << "b = " << FindMin(gn.alleles, 0) << "." << endl;
			cout << "c = " << FindMid(gn.alleles, 0) << "." << endl;
			cout << "d = " << FindMax(gn.alleles, 0) << "." << endl;
			cout << "e = " << BinToDec(gn.alleles, 4) << "." << endl;
			cout << "f = " << BinToDec(gn.alleles, 5) << "." << endl;
			cout << "g = " << FindMin(gn.alleles, 6) << "." << endl;
			cout << "h = " << FindMid(gn.alleles, 7) << "." << endl;
			cout << "i = " << FindMax(gn.alleles, 8) << "." << endl;
			cout << "j = " << BinToDec(gn.alleles, 9) << "." << endl;
			cout << "fitnes = " << gn.fitness << endl;
		}
	}
	else
	{
		char a[] = "-1";
		while (1) {
			while ((strcmp(a, "1") != 0) && (strcmp(a, "2") != 0) && (strcmp(a, "3") != 0) && (strcmp(a, "0") != 0)) {
				puts("-----------Menu-----------");
				puts("| 1. Calculate again      |");
				puts("| 2. Calculate error      |");
				puts("| 3. Input data           |");
				puts("| 0. Return               |");
				puts(" -------------------------");
				scanf("%s", &a);
			}
			if (strcmp(a, "1") == 0) {
				Calculate();
				strcpy(a, "10");
			}
			else if (strcmp(a, "2") == 0) {
				Calculate2();
				strcpy(a, "10");
			}
			else if (strcmp(a, "3") == 0) {
				Calculate3();
				strcpy(a, "10");
			}
			else if (strcmp(a, "0") == 0) return;
		}
	}
}




int main() {
	char a[] = "-1";
	while (1) {
		while ((strcmp(a, "1") != 0) && (strcmp(a, "2") != 0) && (strcmp(a, "3") != 0) && (strcmp(a, "0") != 0)) {
			puts("-----------Menu-----------");
			puts("| 1. Calculate            |");
			puts("| 0. Exit                 |");
			puts(" -------------------------");
			scanf("%s", &a);
		}
		if (strcmp(a, "1") == 0) {
			Calculate();
			strcpy(a, "10");
		}
		else if (strcmp(a, "2") == 0) {
			Calculate2();
			strcpy(a, "10");
		}
		else if (strcmp(a, "0") == 0) return 0;

	}


}