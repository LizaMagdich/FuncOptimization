#pragma once

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

/**
 * The Area class represents parent class for all possible definition areas for the presented functions.
 * Each of the 3 functions has their 3 definition areas.
 */

class Area {
public:
	virtual const char * Name() { return "\0"; }
	void PrintName();
	/**
	 * The function isIn checks if a point is in the definition area.
	 *
	 * @param x is a point
	 * @returns bool value: true --- is inside, false --- isn't inside.
	 */
	virtual  bool isIn(vector<double> x) { return true; }
	virtual ~Area() {};
	vector<double> borders;
};

class RectArea_F_1 : public Area {
public:
	bool isIn(vector<double> x) override;
};

class RectArea_F_2 : public Area {
public:
	bool isIn(vector<double> x) override;
};

class RectArea_F_3 : public Area {
public:
	bool isIn(vector<double> x) override;
};


class Area_1_F_1 : public RectArea_F_1 {
public:
	const char * Name() override;
	Area_1_F_1();
};

class Area_2_F_1 : public RectArea_F_1 {
public:
	const char * Name() override;
	Area_2_F_1();
};

class Area_3_F_1 : public RectArea_F_1 {
public:
	const char * Name() override;
	Area_3_F_1();
};


class Area_1_F_2 : public RectArea_F_2 {
public:
	const char * Name() override;
	Area_1_F_2();
};

class Area_2_F_2 : public RectArea_F_2 {
public:
	const char * Name() override;
	Area_2_F_2();
};

class Area_3_F_2 : public RectArea_F_2 {
public:
	const char * Name() override;
	Area_3_F_2();
};

class Area_1_F_3 : public RectArea_F_3 {
public:
	const char * Name() override;
	Area_1_F_3();
};

class Area_2_F_3 : public RectArea_F_3 {
public:
	const char * Name() override;
	Area_2_F_3();
};

class Area_3_F_3 : public RectArea_F_3 {
public:
	const char * Name() override;
	Area_3_F_3();
};
