#pragma once
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include "fuzzy.h"
using namespace std;
using std::cout;

class functions
{
	protected:
		fuzzy* First;
		fuzzy* Second;
		fuzzy* Result;
	public:
		functions(double, double, double, double, double, double, double, double, double, double);
		~functions();
		double check(double, double);
		double fuzzyMIN(Triangle*, Triangle*, double, double);
		char GetType(Triangle*, Triangle*);
		fuzzy* getf();

};
