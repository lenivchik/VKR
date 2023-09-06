#pragma once
#include <iostream>
#include "rule.h"
class example
{
private:
	int len=23;
	rule* Rules;
public:
	example();
	rule* getRule(int);
	int getLen();
};
