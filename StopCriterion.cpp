#include "pch.h"
#include "StopCriterion.h"

vector<double> Gradient(Function * func, vector<double> x) {
	int dim = x.size();
	vector<double> grad;
	double eps = func->GetEps();
	for (int i = 0; i < dim; ++i) {
		vector<double> temp1;
		temp1 = x;
		temp1[i] += eps;
		grad.push_back((func->eval(temp1) - func->eval(x)) /  eps);
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

bool NormDifOfNodes::Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func, int iterLatestImprov) {
	if (iter == numberMaxIter) { return true; }

	int dim = x1.size();
	vector<double>  dif(dim);
	for (int i = 0; i < dim; ++i) {
		dif[i] = x1[i] - x2[i];
	}

	if (Norm(dif) < eps) { return true; }
	return false;
}

bool NormDifOfValFunc::Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func, int iterLatestImprov) {
	if (iter == numberMaxIter) { return true; }

	vector<double>  dif;
	if (f1 != 0) {
		dif.push_back((f1 - f2) / f1);
	}
	else
	{
		dif.push_back((f1 - f2) / eps);
	}

	if (Norm(dif) < eps) { return true; }
	return false;
}

bool  NormGrad::Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func, int iterLatestImprov) {
	if (iter == numberMaxIter) { return true; }
	vector<double>  grad;
	grad = Gradient(func, x1);

	if (Norm(grad) < eps) { return true; }
	return false;
}


bool ModDifOfNodes::Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func, int iterLatestImprov){
	if (iter == numberMaxIter) { return true; }
	if (abs(f1 - f2) < eps) { return true; }
	return false;
}

bool LatestImprov::Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func, int iterLatestImprov) {
	if (iter == numberMaxIter) { return true; }                                                       
	if (iterLatestImprov > numbMaxIterAfterLastImp) { return true; }
	return false;
}