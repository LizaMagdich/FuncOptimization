#pragma once
#include "pch.h"
#include "Function.h"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
const double step_1 = 10e-3;


double Norm(vector<double> x);
vector<double> Gradient(Function * func, vector<double> x);

/**
 * The StopCriterion class represents the parent class for possible stopping criteria.
 * It has 2 successors:
 * <1> NormDifOfNodes --- stop criterion according to the norm of the difference between last two points
 * <2> NormDifOfValFunc --- stop criterion according to the norm of the difference between values at last two points
 * <3> NormGrad --- stop criterion according to the norm of the gradient value at last point
 *
 * All criteria contain a stop criterion by the number of iterations
 */

class StopCriterion {
public:
	virtual ~StopCriterion() {}
	double eps;
	double step;
	int N;
	/**
	 * The function Stop responsible for stopping optimization.
	 *
	 * @param iter is a number of iterations
	 * @param x1 is a current point
	 * @param x2 is a previous point
	 * @param f1 is a value of the function at current point
	 * @param f2 is a value of the function at previous point
	 * @param func is function pointer
	 * @returns bool value: true --- stop of the optimization, false --- continue the optimization
	 */
	void SetEps(double x) { eps = x; }
	void SetN (int x) { N = x; }

	virtual bool Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func) = 0;
};


class NormDifOfNodes : public StopCriterion {
public:
	bool Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func) override;
};

class NormDifOfValFunc : public StopCriterion {
public:
	bool Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func) override;
};

class NormGrad : public StopCriterion {
public:
	bool Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func) override;
};