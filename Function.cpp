#include "pch.h"
#include "Function.h"

void Function::PrintName() { cout << "I am a function " << Name(); cout << endl; }

const char * F_1::Name() { return "(x1 - 2)^4 + (x1 - 2*x2)^2.\0"; }

const char * F_2::Name() { return "(x1−1)^2+(x2−3*x1)^2+(x3/2−x2/3)^2.\0"; }

const char * F_3::Name() { return "(x1 + 10*x2) + 5*(x3 - x4)^2 + (x2 - 2*x3)^4 + 10*(x1 - x4)^4.\0"; }

double F_1::eval(vector<double> x) {
	return ((x[0] - 2)*(x[0] - 2)*(x[0] - 2)*(x[0] - 2) + (x[0] - 2 * x[1])*(x[0] - 2 * x[1]));
}

double F_2::eval(vector<double> x) {
	return (x[0] - 1)*(x[0] - 1) + (x[1] - 3 * x[0])*(x[1] - 3 * x[0]) + (x[2] / 2. - x[1] / 3.)*(x[2] / 2. - x[1] / 3.);
}

double F_3::eval(vector<double> x) {
	return (x[0] + 10 * x[1]) + 5 * (x[2] - x[3])*(x[2] - x[3]) + (x[1] - 2 * x[2])*(x[1] - 2 * x[2])*(x[1] - 2 * x[2])*(x[1] - 2 * x[2]) + 10 * (x[0] - x[3])*(x[0] - x[3])*(x[0] - x[3])*(x[0] - x[3]);
}
