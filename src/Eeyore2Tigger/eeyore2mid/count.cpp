#include "count.h"

int Counter::paramCount = 0;
int Counter::tempoCount = 0;
int Counter::globaCount = 0;

string Counter::GenParamCode() {
	stringstream trans;
	string paramCode;

	trans << "R_a" << paramCount;
	trans >> paramCode;

	paramCount += 1;

	return paramCode;
}

string Counter::GenTempoCode() {
	stringstream trans;
	string tempoCode;

	trans << "L_e" << tempoCount;
	trans >> tempoCode;

	tempoCount += 1;

	return tempoCode;
}

string Counter::GenGlobaCode() {
	stringstream trans;
	string globaCode;

	trans << "v" << globaCount;
	trans >> globaCode;

	globaCount += 1;

	return globaCode;
}

void Counter::ParamCountInit() {
	paramCount = 0;
}
