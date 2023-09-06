#include "rule.h"


void rule::setRule(double f, double s, double r) {
	first = f;
	second = s;
	result = r;
}

double rule::getFirst() {
	return first;
}
double rule::getSecond() {
	return second;
}
double rule::getResult() {
	return result;
}
