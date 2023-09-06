#include "example.h"
#include <iostream>
#include "rule.h"

example::example() {
	Rules = new rule[len];
	Rules[0].setRule(5, 0.02, 13);
	Rules[1].setRule(21, 0.04, 55);
	Rules[2].setRule(6, 0.06, 19);
	Rules[3].setRule(16, 0.08, 24);
	Rules[4].setRule(25, 0.1, 88);
	Rules[5].setRule(12, 0.13, 54);
	Rules[6].setRule(3, 0.15, 42);
	Rules[7].setRule(28, 0.16, 109);
	Rules[8].setRule(1, 0.18, 57);
	Rules[9].setRule(2, 0.2, 60);
	Rules[10].setRule(24, 0.21, 104);
	Rules[11].setRule(13, 0.24, 102);
	Rules[12].setRule(4, 0.26, 63);
	Rules[13].setRule(9, 0.29, 90);
	Rules[14].setRule(19, 0.3, 61);
	Rules[15].setRule(22, 0.02, 62);
	Rules[16].setRule(4, 0.14, 39);
	Rules[17].setRule(17, 0.07, 35);
	Rules[18].setRule(6, 0.23, 49);
	Rules[19].setRule(8, 0.05, 13);
	Rules[20].setRule(30, 0.27, 114);
	Rules[21].setRule(9, 0.25, 68);
	Rules[22].setRule(14, 0.26, 90);
}

rule* example::getRule(int i) {
	return &Rules[i];
}
int example::getLen() {
	return len;
}
