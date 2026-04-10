#include "Point.h"


void point::init(double x, double y) {
	first = x;
	second = y;
}

void point::Read() {
	cout << "x:  "; 
	cin >> first;
	cout << "y:  ";
	cin >> second;
}

void point::show() {
	cout << "( " << first << " ; " << second << " )" << endl;
}

double point::distance(double x1, double y1) {
	double dx = first - x1;
	double dy = second - y1;
	return sqrt(dx * dx + dy * dy); //евклидово расстояние по формуле
}

point make_point(double x, double y) { //чтобы не писать каждый раз инит
	point p;
	p.init(x, y);
	return p;
}