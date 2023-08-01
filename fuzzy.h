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
	void
		getName() const
	{
		cout << FName << endl;
	}

	void
		getNames1(int i) const
	{
		TriangleRes[i].getName();
	}
	Triangle* GetTriangle(int i);
	Triangle* GetTriangleForResult(char);
	void StartCalculate(Triangle*, double);
	int FindMaxinREsultAll(double,double);
	double ReturnResult();
	void printsp();

};

fuzzy::fuzzy(double left1, double left2, double middle2, double right2, double right1,  bool s) {

	if (!s) {
		TriangleRes = new Triangle[3];
		TriangleRes[0].SetValue(0, 0, left1, low, 'l');
		TriangleRes[1].SetValue(left2, middle2, right2, mid, 'm');
		TriangleRes[2].SetValue(right1, 30, 30, high, 'h');
		FName = new char[strlen("first") + 1];
		strcpy(FName, "first");
	}
	else{
		TriangleRes = new Triangle[3];
		TriangleRes[0].SetValue(0, 0, left1, low, 'l');
		TriangleRes[1].SetValue(left2, middle2, right2, mid, 'm');
		TriangleRes[2].SetValue(right1, 0.3, 0.3, high, 'h');
		FName = new char[strlen("second") + 1];
		strcpy(FName, "second");
	}
	
}

fuzzy::fuzzy() {
		TriangleRes = new Triangle[5];
		TriangleRes[0].SetValue(10, 10, 37, "lowest", 'b');
		TriangleRes[1].SetValue(17, 37, 57, low, 'l');
		TriangleRes[2].SetValue(42, 62, 82, mid, 'm');
		TriangleRes[3].SetValue(67, 87, 107, high, 'h');
		TriangleRes[4].SetValue(95, 115, 120, "highest", 'p');
		FName = new char[strlen("result") + 1];
		strcpy(FName, "result");
}

fuzzy::~fuzzy() {
	delete FName; 
	FName = NULL;
	delete[] TriangleRes;

}

Triangle* fuzzy :: GetTriangle(int i) {
	return &TriangleRes[i];
}

Triangle* fuzzy::GetTriangleForResult (char r) {
	for (int i = 0; i < 5; i++) {
		if (TriangleRes[i].getType(r))
			return &TriangleRes[i];
	}

}
void fuzzy::StartCalculate(Triangle* CurTr, double min) {
	if (min > 0) {
		double left, right, res;
		left = CurTr->GetLeft();
		right = CurTr->GetRight();
		for (left; left <= right; left += 1) {
			res = CurTr->getResult(left, min);
			if (FindMaxinREsultAll(left, res)) {
				ResultAll* Result = new ResultAll();
				Result->x = left;
				Result->y = res;
				Result->Next = Head;
				Head = Result;
			}
		}
	}
}

int fuzzy::FindMaxinREsultAll(double curx,double res) {
	ResultAll* p = Head;
	while (p)
	{
		if (p->x == curx) {
			if (p->y < res) {
				p->y = res;
			}
			return 0;
		}
			

		p = p->Next;
	}
	return 1;
}

double fuzzy::ReturnResult() {
	//printsp();
	int i = 0;
	double up = 0, down = 0, res;
	double x1, x2, y1, y2, z;
	ResultAll* p = Head;
	if (!p) {
		return 0;
	}
	while (p->Next)
	{
		x1 = p->x;
		y1 = p->y;
		x2 = p->Next->x;
		y2 = p->Next->y;
		z = (y1 < y2) ? ((x1 + x2) * y1 + (y2 - y1) * (x2 + (x1 - x2) / 3))
					  : ((x1 + x2) * y2 + (y1 - y2) * (x2 + 2 * (x1 - x2) / 3));
		/*cout << "x1 " << x1 << " y1 " << y1 << " x2 " <<x2 << " y2 " << y2 << "z " << (0.5 * (x1 - x2) * z) / (0.5 * (x1 - x2) * (y1 + y2))<< "\n";*/
		up = up + 0.5 * (x1 - x2) * z;
		down = down + 0.5 * (x1 - x2) * (y1 + y2);
		/*cout << "x1 " << x1 << " y1 " << y1 << " x2 " << x2 << " y2 " << y2 << "up " << up<< " down " << down << "\n";*/
		p = p->Next;
	}
	res = up / down;
	DEll();
	/*cout << " up " << up << " down " << down << " res "<< res<<  "\n";*/
	return res;
}
void fuzzy::printsp() {
	ResultAll* p = Head;
	cout << "strat\n";
	while (p)
	{
		cout << "x " << p->x << " y " << p->y << "\n";
		p = p->Next;
	}
	cout << "end\n";
 }

void fuzzy::DEll() {
	ResultAll* p = Head;
	while (Head)
	{
		ResultAll* p = Head;
		Head = Head->Next;
		delete p;
	}

}





