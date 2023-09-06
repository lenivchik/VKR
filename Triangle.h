#pragma once
using namespace std;


class Triangle
{
private:
	double Left;
	double Right;
	double Middle;
	char* tName;
	char tType;

public:
	~Triangle();
	double getValue(double t);
	void SetValue(double, double, double, const char*, char);
	double getResult(double,double);
	double GetLeft();
	double GetRight();
	bool getType(char type);
	void getName();
	char* getFullName();
};
