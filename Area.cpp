#include "pch.h"
#include "Area.h"


void Area::PrintName() { cout << "Area is " << Name(); cout << endl; }

bool  RectArea_F_1::isIn(vector<double> x) {
	if (borders[0] - eps < x[0] && x[0] < borders[1] + eps && borders[2] - eps < x[1] && x[1] < borders[3] + eps) return true;
	else return false;
}

bool  RectArea_F_2::isIn(vector<double> x) {
	if (borders[0] - eps < x[0] && x[0] < borders[1] + eps && borders[2] - eps < x[1] && x[1] < borders[3] + eps && borders[4] - eps < x[2] && x[2] < borders[5] + eps) return true;
	else return false;
}

bool  RectArea_F_3::isIn(vector<double> x) {
	if (borders[0] - eps < x[0] && x[0] < borders[1] + eps && borders[2] - eps < x[1] && x[1] < borders[3] + eps && borders[4] - eps < x[2] && x[2] < borders[5] + eps && borders[6] - eps < x[3] && x[3] < borders[7] + eps) return true;
	else return false;
}

const char * Area_1_F_1::Name() { return "[0 ; 3]^2\0"; }

Area_1_F_1::Area_1_F_1() {
	borders.push_back(0);
	borders.push_back(3);
	borders.push_back(0);
	borders.push_back(3);
}

const char * Area_2_F_1::Name() { return "[-5 ; 5]^2\0"; }

Area_2_F_1::Area_2_F_1() {
	borders.push_back(-5);
	borders.push_back(5);
	borders.push_back(-5);
	borders.push_back(5);
}

const char * Area_3_F_1::Name() { return "[0 ; 3]*[0; 6]\0"; }

Area_3_F_1::Area_3_F_1() {
	borders.push_back(0);
	borders.push_back(3);
	borders.push_back(0);
	borders.push_back(6);
}

const char * Area_1_F_2::Name() { return "[0 ; 3]^3\0"; }

Area_1_F_2::Area_1_F_2() {
	borders.push_back(0);
	borders.push_back(3);
	borders.push_back(0);
	borders.push_back(3);
	borders.push_back(0);
	borders.push_back(3);
}

const char * Area_2_F_2::Name() { return "[-5 ; 5]^3\0"; }

Area_2_F_2::Area_2_F_2() {
	borders.push_back(-5);
	borders.push_back(5);
	borders.push_back(-5);
	borders.push_back(5);
	borders.push_back(-5);
	borders.push_back(5);
}

const char * Area_3_F_2::Name() { return "[0 ; 3]*[0; 6]*[0, 2]\0"; }

Area_3_F_2::Area_3_F_2() {
	borders.push_back(0);
	borders.push_back(3);
	borders.push_back(0);
	borders.push_back(6);
	borders.push_back(0);
	borders.push_back(2);
}

const char * Area_1_F_3::Name() { return "[0 ; 3]^4\0"; }

Area_1_F_3::Area_1_F_3() {
	borders.push_back(0);
	borders.push_back(3);
	borders.push_back(0);
	borders.push_back(3);
	borders.push_back(0);
	borders.push_back(3);
	borders.push_back(0);
	borders.push_back(3);
}

const char * Area_2_F_3::Name() { return "[-5 ; 5]^4\0"; }

Area_2_F_3::Area_2_F_3() {
	borders.push_back(-5);
	borders.push_back(5);
	borders.push_back(-5);
	borders.push_back(5);
	borders.push_back(-5);
	borders.push_back(5);
	borders.push_back(-5);
	borders.push_back(5);
}

const char * Area_3_F_3::Name() { return "[0 ; 3]*[0; 6]*[0, 2]*[0, 1]\0"; }

Area_3_F_3::Area_3_F_3() {
	borders.push_back(0);
	borders.push_back(3);
	borders.push_back(0);
	borders.push_back(6);
	borders.push_back(0);
	borders.push_back(2);
	borders.push_back(0);
	borders.push_back(1);
}