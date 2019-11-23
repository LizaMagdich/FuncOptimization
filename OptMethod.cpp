#include "pch.h"
#include "OptMethod.h"
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

const double deltaStart = 10e-2;


double StohasticSearch::Optimize(Area * area, Function * func, StopCriterion * stopCrit, int * iter) {
	int dim = func->GetDimension();
	double p = prob, delta = deltaStart;
	
	vector<double> currentPoint;
	vector<double> previousePoint;
	previousePoint = currentPoint = StartPoint;
	double currentValueInPoint = func->eval(currentPoint);

	StopCriterion * stopCritForFist = new NormGrad;
	stopCritForFist->SetEps(stopCrit->GetEps());
	if (stopCritForFist->Stop(0, StartPoint, StartPoint, currentValueInPoint, currentValueInPoint, func)) { *iter = 0; xFin = StartPoint; delete stopCritForFist;  return currentValueInPoint; }
	delete stopCritForFist;

	double eps = stopCrit->eps;
	int N = stopCrit->numberMaxIter;
	for (int i = 1; ; ++i) {
		vector<double> newPoint;
		std::uniform_real_distribution<> dist(0, 1);
		double alpha = dist(gen);
		bool flagSmallVicinity = 0;
		if (p - alpha > eps) {
			int index = 0;
			for (int i = 0; i < dim ; ++i, index+=2){
				vector<double> borders;
				borders.push_back(area->GetBorderI(index));
				borders.push_back(area->GetBorderI(index+1));
				flagSmallVicinity = 1;
				double a, b;
				(currentPoint[i] - delta) - borders[0] > eps ? a = currentPoint[i] - delta : a = borders[0];
				borders[1] - (currentPoint[i] + delta) > eps ? b = currentPoint[i] + delta : b = borders[1];
				std::uniform_real_distribution<> dis(a, b);
				newPoint.push_back(dis(gen));
			}
		}
		else {
			for (int i = 0; i < dim * 2; i = i + 2) {
				std::uniform_real_distribution<> dis(area->borders[i], area->borders[i + 1]);
				newPoint.push_back(dis(gen));
			}
		}
		

		double temp = func->eval(newPoint);
		if (currentValueInPoint - temp > eps) {
			previousePoint = currentPoint;
			currentPoint = newPoint;
			currentValueInPoint = temp;
			if (stopCrit->Stop(i, currentPoint, previousePoint, currentValueInPoint, func->eval(previousePoint), func)) { *iter = i; xFin = currentPoint;  return  currentValueInPoint; }
			if (flagSmallVicinity) {
				delta /= 2;
			}
		}
		if (i == N) { *iter = i; xFin = currentPoint;  return  currentValueInPoint; }
	}
}

double CoordinateDescent::Optimize(Area * area, Function * func, StopCriterion * stopCrit, int * iter) {
	int dim = func->GetDimension();
	double  minFuncValue = func->eval(StartPoint);
	StopCriterion * stopCritForFist = new NormGrad;
	stopCritForFist->SetEps(stopCrit->GetEps());
	if (stopCritForFist->Stop(0, StartPoint, StartPoint, minFuncValue, minFuncValue, func)) { *iter = 0; xFin = StartPoint; delete stopCritForFist;  return minFuncValue; }
	delete stopCritForFist;

	double eps = stopCrit->eps;

	vector<double> currentPoint(dim);
	vector<double>  previousePoint(dim);
	vector<double> tempCurrentPoint(dim);
	vector<double> tempPreviousePoint(dim);

	currentPoint = tempCurrentPoint = StartPoint;

	for (int j = 1; ; ++j) {

		int index = 0;
		for (int i = 0; i < dim; ++i, index +=2) {
			
			vector<double> borders;
			borders.push_back(area->GetBorderI(index));
			borders.push_back((2* area->GetBorderI(index) + area->GetBorderI(index + 1)) / 3);
			borders.push_back((area->GetBorderI(index) + 2 * area->GetBorderI(index + 1)) / 3);
			borders.push_back(area->GetBorderI(index + 1));

			vector<double> pointsOfMinFunc;
			vector<double> MinValFunc;
			for (int ii = 0; ii < 3; ++ii) {
				double leftBorder = borders[ii], rightBorder = borders[ii + 1];
				bool flagFirstIter = 1, flagRemRightBorder;
				double f;
				double tempLeftBorder, tempRightBorder;
				while (rightBorder - leftBorder > eps)
				{
					if (flagFirstIter) {
						flagFirstIter = 0;
						tempLeftBorder = rightBorder - (rightBorder - leftBorder) / goldenRatio;
						tempRightBorder = leftBorder + (rightBorder - leftBorder) / goldenRatio;
						vector<double> tempPoint1 = tempCurrentPoint, tempPoint2 = tempCurrentPoint;
						tempPoint1[i] = tempLeftBorder;
						tempPoint2[i] = tempRightBorder;
						double f1 = func->eval(tempPoint1), f2 = func->eval(tempPoint2);
						if (f1 < f2) {
							rightBorder = tempRightBorder;
							f = f1;
							flagRemRightBorder = 1;
							tempRightBorder = tempLeftBorder;
						}
						else
						{
							leftBorder = tempLeftBorder;
							f = f2;
							flagRemRightBorder = 0;
							tempLeftBorder = tempRightBorder;
						}
					}
					else
					{
						if (flagRemRightBorder) {
							tempLeftBorder = rightBorder - (rightBorder - leftBorder) / goldenRatio;
							vector<double> tempPoint = tempCurrentPoint;
							tempPoint[i] = tempLeftBorder;
							double f1 = func->eval(tempPoint);
							if (f1 < f) {
								rightBorder = tempRightBorder;
								f = f1;
								flagRemRightBorder = 1;
								tempRightBorder = tempLeftBorder;
							}
							else
							{
								leftBorder = tempLeftBorder;
								flagRemRightBorder = 0;
								tempLeftBorder = tempRightBorder;
							}
						}
						else
						{
							tempRightBorder = leftBorder + (rightBorder - leftBorder) / goldenRatio;
							vector<double> tempPoint = tempCurrentPoint;
							tempPoint[i] = tempRightBorder;
							double f2 = func->eval(tempPoint);
							if (f < f2) {
								rightBorder = tempRightBorder;
								
								flagRemRightBorder = 1;
								tempRightBorder = tempLeftBorder;
							}
							else
							{
								leftBorder = tempLeftBorder;
								flagRemRightBorder = 0;
								f = f2;
								tempLeftBorder = tempRightBorder;
							}
						}
					}
				}

				pointsOfMinFunc.push_back((leftBorder + rightBorder) / 2);
				vector<double> tempPoint = tempCurrentPoint;
				tempPoint[i] = pointsOfMinFunc[ii];
				MinValFunc.push_back(func->eval(tempPoint));
				
			}
			std::vector<double>::iterator result = std::min_element(MinValFunc.begin(), MinValFunc.end());
			int indMinValFunc = std::distance(MinValFunc.begin(), result);

			tempPreviousePoint = tempCurrentPoint;
			tempCurrentPoint[i] = pointsOfMinFunc[indMinValFunc];
			minFuncValue = MinValFunc[indMinValFunc];
		}

		previousePoint = currentPoint;
		currentPoint = tempCurrentPoint;
		
		if (stopCrit->Stop(j, currentPoint, previousePoint, minFuncValue, func->eval(previousePoint), func)) { *iter = j; xFin = currentPoint;  return  minFuncValue; }
	}

}
