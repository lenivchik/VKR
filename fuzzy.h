#pragma once
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include "Triangle.h"

using namespace std;
struct ResultAll {
	int x;
	double y;
	ResultAll* Next;
};
class fuzzy
{
protected:
	double dLeft1, dRight1, dMiddle1, dLeft2, dRight2, dMiddle2;;
	char* FName;
	char low[4]= "low";
	char mid[8]= "middle"; 
	char high[5] ="high";
	Triangle* TriangleRes;
	ResultAll* Head;
	void DEll();

public:
	fuzzy(double, double, double, double, double, bool);
	fuzzy();
	~fuzzy();
	void getName(); 
	void getNames1(int i);
	Triangle* GetTriangle(int i);
	Triangle* GetTriangleForResult(char);
	void StartCalculate(Triangle*, double);
	int FindMaxinREsultAll(double,double);
	double ReturnResult();
	void printsp();
};






