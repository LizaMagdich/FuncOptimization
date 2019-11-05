#include "pch.h"
#include "OptMethod.h"
#include <random>

std::random_device rd;
std::mt19937 gen(rd());


double StohasticSearch::Optimize(Area * area, Function * func, StopCriterion * stopCrit, int * iter) {
	int dim = func->GetDimension();
	cout << "Print the starting point in the area of dimension " << dim << ". ";
	area->PrintName();

	vector<double>  startPoint(dim);
	for (int i = 0; i < dim; ++i) {
		if (i == 0) { cout << "Print the first coordinate." << endl; }
		else { cout << "Print the next coordinate." << endl; };
		cin >> startPoint[i];
	}
	while (!area->isIn(startPoint)) {
		cout << "Print the starting point in the area of dimension. " << dim;
		area->PrintName();
		for (int i = 0; i < dim; ++i) {
			if (i == 0) { cout << "Print the first coordinate." << endl; }
			else { cout << "Print the next coordinate." << endl; };
			cin >> startPoint[i];
		}
	}

	x0 = startPoint;
	vector<double> currentPoint;
	vector<double> previousePoint;
	previousePoint = currentPoint = startPoint;
	double currentValueInPoint = func->eval(currentPoint);

	StopCriterion * stopCritForFist = new NormGrad;
	if (stopCritForFist->Stop(0, startPoint, startPoint, currentValueInPoint, currentValueInPoint, func)) { *iter = 0; xFin = startPoint; delete stopCritForFist;  return currentValueInPoint; }
	delete stopCritForFist;

	for (int i = 1; ; ++i) {
		vector<double> newPoint;
		for (int i = 0; i < dim * 2; i = i + 2) {
			std::uniform_real_distribution<> dis(area->borders[i], area->borders[i + 1]);
			newPoint.push_back(dis(gen));
		}

		double temp = func->eval(newPoint);
		if (currentValueInPoint - temp > eps) {
			previousePoint = currentPoint;
			currentPoint = newPoint;
			currentValueInPoint = temp;
			if (stopCrit->Stop(i, currentPoint, previousePoint, currentValueInPoint, func->eval(previousePoint), func)) { *iter = i; xFin = currentPoint;  return  currentValueInPoint; }
		}
		if (i == N) { *iter = i; xFin = currentPoint;  return  currentValueInPoint; }
	}
}

double CoordinateDescent::Optimize(Area * area, Function * func, StopCriterion * stopCrit, int * iter) {
	int dim = func->GetDimension();
	cout << "Print the starting point in the area of dimension " << dim << ". ";
	area->PrintName();

	vector<double>  startPoint(dim);
	for (int i = 0; i < dim; ++i) {
		if (i == 0) { cout << "Print the first coordinate." << endl; }
		else { cout << "Print the next coordinate." << endl; };
		cin >> startPoint[i];
	}
	while (!area->isIn(startPoint)) {
		cout << "Print the starting point in the area of dimension. " << dim;
		area->PrintName();
		for (int i = 0; i < dim; ++i) {
			if (i == 0) { cout << "Print the first coordinate." << endl; }
			else { cout << "Print the next coordinate." << endl; };
			cin >> startPoint[i];
		}
	}

	x0 = startPoint;
	double  minFuncValue = func->eval(startPoint);
	StopCriterion * stopCritForFist = new NormGrad;
	if (stopCritForFist->Stop(0, startPoint, startPoint, minFuncValue, minFuncValue, func)) { *iter = 0; xFin = startPoint; delete stopCritForFist;  return minFuncValue; }
	delete stopCritForFist;

	vector<double> currentPoint(dim);
	vector<double>  previousePoint(dim);
	vector<double> tempCurrentPoint(dim);
	vector<double> tempPreviousePoint(dim);

	currentPoint = tempCurrentPoint = startPoint;

	double minFuncValueInPositiveDirection = minFuncValue, minFuncValueInNegativeDirection = minFuncValue;
	double bestMinimizingLambdaInPositiveDirection = 0, bestMinimizingLambdaInNegativeDirection = 0, bestMinimizingLambda = 0;
	double lambda = 0;

	for (int j = 1; ; ++j) {

		for (int i = 0; i < dim; ++i, bestMinimizingLambdaInPositiveDirection = bestMinimizingLambdaInNegativeDirection = bestMinimizingLambda = 0) {

			vector<double> nextPointByCurrentDirection(dim);
			nextPointByCurrentDirection = tempCurrentPoint;

			for (lambda = step, nextPointByCurrentDirection[i] += step; ; nextPointByCurrentDirection[i] += step, lambda += step) {

				if (!area->isIn(nextPointByCurrentDirection)) { break; }
				double temp = func->eval(nextPointByCurrentDirection);

				if (minFuncValueInPositiveDirection - temp > eps) {
					minFuncValueInPositiveDirection = temp;
					bestMinimizingLambdaInPositiveDirection = lambda;
				}
			}


			nextPointByCurrentDirection = tempCurrentPoint;


			for (lambda = -step, nextPointByCurrentDirection[i] -= step; ; nextPointByCurrentDirection[i] -= step, lambda -= step) {

				if (!area->isIn(nextPointByCurrentDirection)) { break; }
				double temp = func->eval(nextPointByCurrentDirection);

				if (minFuncValueInNegativeDirection - temp > eps) {
					minFuncValueInNegativeDirection = temp;
					bestMinimizingLambdaInNegativeDirection = lambda;
				}
			}


			if (minFuncValueInPositiveDirection - minFuncValueInNegativeDirection > eps) {
				minFuncValue = minFuncValueInNegativeDirection;
				bestMinimizingLambda = bestMinimizingLambdaInNegativeDirection;
			}
			else
			{
				minFuncValue = minFuncValueInPositiveDirection;
				bestMinimizingLambda = bestMinimizingLambdaInPositiveDirection;
			}

			tempPreviousePoint = tempCurrentPoint;
			tempCurrentPoint[i] = tempPreviousePoint[i] + bestMinimizingLambda;
			minFuncValueInPositiveDirection = minFuncValueInNegativeDirection = minFuncValue;
		}

		previousePoint = currentPoint;
		currentPoint = tempCurrentPoint;

		if (stopCrit->Stop(j, currentPoint, previousePoint, minFuncValue, func->eval(previousePoint), func)) { *iter = j; xFin = currentPoint;  return  minFuncValue; }
	}

}
