#include "functions.h"

functions::functions(double x1, double x2, double x3, double x4, double x5, double y1, double y2, double y3, double y4, double y5) {
	First = new fuzzy(x1, x2, x3, x4, x5, 0);
	Second = new fuzzy(y1, y2, y3, y4, y5, 1);
	Result = new fuzzy();
}
functions::~functions() {
	delete First, Second, Result;
}

fuzzy* functions::getf() {
	return First;
}
double functions::check(double firstnum, double secondnum) {
	Triangle* first, * second;
	int num = 0;
	double test = 0.15;
	for (int i = 0; i < 3; i++) {
		first = First->GetTriangle(i);
		for (int j = 0; j < 3; j++) {
			second = Second->GetTriangle(j);
			/*cout << "first " << first->getFullName()<< " second "<< second->getFullName()<<" result "<< Result->GetTriangleForResult(GetType(first, second))->getFullName()<<"\n";
			cout << "first " << first->getValue(firstnum) << " second " << second->getValue(secondnum) << " first function value "<< firstnum << " second function value " << secondnum<<"\n";
			cout << "Min "<< fuzzyMIN(first, second, firstnum, secondnum) << "\n";
			cout <<"\n";*/


			Result->StartCalculate(Result->GetTriangleForResult(GetType(first, second)), fuzzyMIN(first, second, firstnum, secondnum));
		}
	}
	return Result->ReturnResult();

}

double functions::fuzzyMIN(Triangle* A, Triangle* B, double firstnum, double secondnum) {
	double f = A->getValue(firstnum);
	double s = B->getValue(secondnum);

	return (f < s) ? f : s;
}

char functions::GetType(Triangle* first, Triangle* second) {
	char* rule1 = new char[8];
	char* rule2 = new char[8];
	char res = 'a';
	strcpy(rule1, first->getFullName());
	strcpy(rule2, second->getFullName());


	if (0 == strcmp(rule1, "low") && 0 == strcmp(rule2, "low")) {
		res = 'b';
	}
	else if (0 == strcmp(rule1, "middle") && 0 == strcmp(rule2, "low")) {
		res = 'l';
	}
	else if (0 == strcmp(rule1, "high") && 0 == strcmp(rule2, "low")) {
		res = 'm';
	}
	else if (0 == strcmp(rule1, "low") && 0 == strcmp(rule2, "middle")) {
		res = 'l';
	}
	else if (0 == strcmp(rule1, "middle") && 0 == strcmp(rule2, "middle")) {
		res = 'm';
	}
	else if (0 == strcmp(rule1, "high") && 0 == strcmp(rule2, "middle")) {
		res = 'h';
	}
	else if (0 == strcmp(rule1, "low") && 0 == strcmp(rule2, "high")) {
		res = 'm';
	}
	else if (0 == strcmp(rule1, "middle") && 0 == strcmp(rule2, "high")) {
		res = 'h';
	}
	else if (0 == strcmp(rule1, "high") && 0 == strcmp(rule2, "high")) {
		res = 'p';
	}

	delete[] rule1, rule2;
	return res;
}
