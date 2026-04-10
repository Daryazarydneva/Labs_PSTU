#pragma once
#include <cmath>
#include <iostream>
using namespace std;

class point {
	double first;    //координата х
	double second;   //координата у

public:

	void init(double x, double y); //инициализация
	
	void Read(); //ввод значений с клавиатуры, чтение

	void show(); //вывод значений
	
	double distance(double x1, double x2); //дистанция
	
	double GetX() const { return first; }
	double GetY() const { return second; }
	
};
point make_point(double x, double y);
