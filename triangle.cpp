#include "Triangle.h"
#include <iostream>
using std::cout;

bool Triangle::getType(char type) {
	if (type == tType)
		return true;
	return false;
}
void Triangle::getName()
{
	cout << tName << endl;
}

char* Triangle::getFullName()
{
	return tName;
}

Triangle::~Triangle() {
	delete[] tName;
}
double Triangle::getValue(double t) {
	if (Left > Middle)
		return 0;
	if (Middle > Right)
		return 0;
	//if (Left == Middle && t <= Left && tType=='l')
	//	return 1;
	//if (Right == Middle && t >= Right && tType == 'h')
	//	return 1;
	if (t <= Left)
		return 0;
	else if (t < Middle)
		return (t - Left) / (Middle - Left);
	else if (t == Middle)
		return 1.0;
	else if (t < Right)
		return (Right - t) / (Right - Middle);
	else
		return 0;
}

void Triangle::SetValue(double left, double  middle, double right, const char* s, char t) {
	Right = right;
	Left = left;
	Middle = middle;
	tName = new char[strlen(s) + 1];
	strcpy(tName, s);
	tType = t;
}


double Triangle::getResult(double x, double min) {
	double result, y;
	result = 0;
	if ((y = getValue(x)) <= min)
		return y;
	else
		return min;
}

double Triangle::GetLeft() {
	return Left;
}


double Triangle::GetRight() {
	return Right;
}
