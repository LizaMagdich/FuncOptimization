// FuncOptimization.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "OptMethod.h"

int main()
{
	Function * func = nullptr;
	Area * area = nullptr;
	OptMethod * method = nullptr;;
	StopCriterion* stopCrit = nullptr;;
	int flagFunc, flagArea, flagMethod, flagStopCrite;

	cout << "What method of optimization do you want to choose?" << endl << endl << "Print 1 to choose Coordinate Descent." << endl;
	cout << "Print 2 to choose Stohastic Search." << endl;
	cin >> flagMethod;
	while (flagMethod != 1 && flagMethod != 2) {
		cout << "Print 1 to choose Coordinate Descent." << endl << "Print 2 to choose Stohastic Search." << endl;
		cin >> flagMethod;
	}

	if (flagMethod == 1) {
		method = new CoordinateDescent;
	}

	if (flagMethod == 2) {
		method = new StohasticSearch;
	}

	cout << "What stop criterion do you want to choose?" << endl << endl << "Print 1 to choose criterion ||x_k - x_k-1 || < eps." << endl;
	cout << "Print 2 to choose criterion ||(F_k - F_k-1)/F_k || < eps." << endl << "Print 3 to choose criterion || gr(F_k )|| < eps." << endl;
	cin >> flagStopCrite;
	while (flagStopCrite != 1 && flagStopCrite != 2 && flagStopCrite != 3) {
		cout << "Print 1 to choose criterion ||x_k - x_k-1 || < eps." << endl;
		cout << "Print 2 to choose criterion ||(F_k - F_k-1)/F_k || < eps." << endl;
		cout << "Print 3 to choose criterion || gr(F_k )|| < eps." << endl;
		cin >> flagStopCrite;
	}
	if (flagStopCrite == 1) {
		stopCrit = new NormDifOfNodes;
	}

	if (flagStopCrite == 2) {
		stopCrit = new NormDifOfValFunc;
	}
	if (flagStopCrite == 3) {
		stopCrit = new NormGrad;
	}

	cout << "What function do you want to choose?" << endl << endl;
	cout << "Print 1 to choose (x1 - 2)^4 + (x1 - 2*x2)^2" << endl;
	cout << "Print 2 to choose (x1-1)^2+(x2-3*x1)^2+(x3/2-x2/3)^2" << endl;
	cout << "Print 3 to choose (x1 + 10*x2) + 5*(x3 - x4)^2 + (x2 - 2*x3)^4 + 10*(x1 - x4)^4" << endl;
	cin >> flagFunc;
	while (flagFunc != 1 && flagFunc != 2 && flagFunc != 3) {
		cout << "Print 1 to choose (x1 - 2)^4 + (x1 - 2*x2)^2" << endl;
		cout << "Print 2 to choose (x1-1)^2+(x2-3*x1)^2+(x3/2-x2/3)^2" << endl;
		cout << "Print 3 to choose (x1 + 10*x2) + 5*(x3 - x4)^2 + (x2 - 2*x3)^4 + 10*(x1 - x4)^4" << endl;
		cin >> flagFunc;
	}

	if (flagFunc == 1) {
		func = new F_1;
		cout << "What area do you want to choose?" << endl << endl << "Print 1 to choose [0 ; 3]^2" << endl;
		cout << "Print 2 to choose [-5 ; 5]^2" << endl << "Print 3 to choose [0 ; 3]*[0; 6] " << endl;

		cin >> flagArea;
		while (flagArea != 1 && flagArea != 2 && flagArea != 3) {
			cout << "Print 1 to choose [0 ; 3]^2" << endl << "Print 2 to choose [-5 ; 5]^2" << endl << "Print 3 to choose [0 ; 3]*[0; 6] " << endl;
			cin >> flagArea;
		}

		if (flagArea == 1) {
			area = new Area_1_F_1;
			int  iter = 0;
			cout << "Minimum of functin  " << method->Optimize(area, func, stopCrit, &iter) << endl << "Final point ";
			for (int i = 0; i < func->GetDimension(); ++i) {
				cout << method->xFin[i] << " ";
			}
			cout << endl;
			cout << "Number of iterations: " << iter << endl;
			delete area;
		}

		if (flagArea == 2) {
			area = new Area_2_F_1;
			int iter = 0;
			cout << "Minimum of functin " << method->Optimize(area, func, stopCrit, &iter) << endl << "Final point ";
			for (int i = 0; i < func->GetDimension(); ++i) {
				cout << method->xFin[i] << " ";
			}
			cout << endl;
			cout << "Number of iterations: " << iter << endl;
			delete area;
		}

		if (flagArea == 3) {
			area = new Area_3_F_1;
			int iter = 0;
			cout << "Minimum of functin " << method->Optimize(area, func, stopCrit, &iter) << endl << "Final point ";
			for (int i = 0; i < func->GetDimension(); ++i) {
				cout << method->xFin[i] << " ";
			}
			cout << endl;
			cout << "Number of iterations: " << iter << endl;
			delete area;
		}
		delete func;
	}

	if (flagFunc == 2) {
		func = new F_2;
		cout << "What area do you want to choose?" << endl << endl << "Print 1 to choose [0 ; 3]^3" << endl;
		cout << "Print 2 to choose [-5 ; 5]^3" << endl << "Print 3 to choose [0 ; 3]*[0; 6]*[0, 2]" << endl;

		cin >> flagArea;
		while (flagArea != 1 && flagArea != 2 && flagArea != 3) {
			cout << "Print 1 to choose [0 ; 3]^3" << endl << "Print 2 to choose [-5 ; 5]^3" << endl << "Print 3 to choose [0 ; 3]*[0; 6]*[0, 2]" << endl;
			cin >> flagArea;
		}

		if (flagArea == 1) {
			area = new Area_1_F_2;
			int iter = 0;
			cout << "Minimum of functin  " << method->Optimize(area, func, stopCrit, &iter) << endl << "Final point ";
			for (int i = 0; i < func->GetDimension(); ++i) {
				cout << method->xFin[i] << " ";
			}
			cout << endl;
			cout << "Number of iterations: " << iter << endl;
			delete area;
		}

		if (flagArea == 2) {
			area = new Area_2_F_2;
			int iter = 0;
			cout << "Minimum of functin " << method->Optimize(area, func, stopCrit, &iter) << endl << "Final point ";
			for (int i = 0; i < func->GetDimension(); ++i) {
				cout << method->xFin[i] << " ";
			}
			cout << endl;
			cout << "Number of iterations: " << iter << endl;
			delete area;
		}

		if (flagArea == 3) {
			area = new Area_3_F_2;
			int iter = 0;
			cout << "Minimum of functin " << method->Optimize(area, func, stopCrit, &iter) << endl << "Final point ";
			for (int i = 0; i < func->GetDimension(); ++i) {
				cout << method->xFin[i] << " ";
			}
			cout << endl;
			cout << "Number of iterations: " << iter << endl;
			delete area;
		}
		delete func;
	}

	if (flagFunc == 3) {
		func = new F_3;
		cout << "What area do you want to choose?" << endl << endl << "Print 1 to choose [0 ; 3]^4" << endl;
		cout << "Print 2 to choose [-5 ; 5]^4" << endl << "Print 3 to choose [0 ; 3]*[0; 6]*[0, 2]*[0, 1]" << endl;

		cin >> flagArea;
		while (flagArea != 1 && flagArea != 2 && flagArea != 3) {
			cout << "Print 1 to choose [0 ; 3]^4" << endl << "Print 2 to choose [-5 ; 5]^4" << endl << "Print 3 to choose [0 ; 3]*[0; 6]*[0, 2]*[0, 1]" << endl;
			cin >> flagArea;
		}

		if (flagArea == 1) {
			area = new Area_1_F_3;
			int iter = 0;
			cout << "Minimum of functin  " << method->Optimize(area, func, stopCrit, &iter) << endl << "Final point ";
			for (int i = 0; i < func->GetDimension(); ++i) {
				cout << method->xFin[i] << " ";
			}
			cout << endl;
			cout << "Number of iterations: " << iter << endl;
			delete area;
		}

		if (flagArea == 2) {
			area = new Area_2_F_3;
			int iter = 0;
			cout << "Minimum of functin " << method->Optimize(area, func, stopCrit, &iter) << endl << "Final point ";
			for (int i = 0; i < func->GetDimension(); ++i) {
				cout << method->xFin[i] << " ";
			}
			cout << endl;
			cout << "Number of iterations: " << iter << endl;
			delete area;
		}

		if (flagArea == 3) {
			area = new Area_3_F_3;
			int iter = 0;
			cout << "Minimum of functin " << method->Optimize(area, func, stopCrit, &iter) << endl << "Final point ";
			for (int i = 0; i < func->GetDimension(); ++i) {
				cout << method->xFin[i] << " ";
			}
			cout << endl;
			cout << "Number of iterations: " << iter << endl;
			delete area;
		}

		delete func;
	}
	delete method;
	delete stopCrit;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
