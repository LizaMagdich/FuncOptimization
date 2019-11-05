#include "pch.h"
#include "StopCriterion.h"
#include "Function.h"

vector<double> Gradient(Function * func, vector<double> x) {
	int dim = x.size();
	vector<double> grad;
	for (int i = 0; i < dim; ++i) {
		vector<double> temp1(dim);
		vector<double> temp2(dim);
		temp1 = temp2 = x;
		temp1[i] += step;
		temp2[i] -= step;
		grad.push_back((func->eval(temp1) - func->eval(temp2)) / (2 * step));
		temp1[i] = x[i];
		temp2[i] = x[i];
	}

	return grad;
}


double Norm(vector<double> x) {
	double temp = 0;
	for (int i = 0; i < x.size(); ++i) {
		temp += x[i] * x[i];
	}
	return sqrt(temp);
}

bool NormDifOfNodes::Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func) {
	if (iter == N) { return true; }

	int dim = x1.size();
	vector<double>  dif(dim);
	for (int i = 0; i < dim; ++i) {
		dif[i] = x1[i] - x2[i];
	}

	if (Norm(dif) < eps) { return true; }
	return false;
}

bool NormDifOfValFunc::Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func) {
	if (iter == N) { return true; }

	vector<double>  dif;
	if (f1 != 0) {
		dif.push_back((f2 - f1) / f1);
	}
	else
	{
		dif.push_back((f2 - f1) / step);
	}

	if (Norm(dif) < eps) { return true; }
	return false;
}

bool  NormGrad::Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func) {
	if (iter == N) { return true; }
	vector<double>  grad;
	grad = Gradient(func, x1);

	if (Norm(grad) < eps) { return true; }
	return false;
}
