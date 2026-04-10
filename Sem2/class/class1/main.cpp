#include "Point.h"

int main() {
	setlocale(LC_ALL, "Russian");

	//создание через инит
	point A;
	A.init(3.5, 2.0);
	cout << "точка А:  " << endl;
	A.show();

	//через риад
	point B;
	cout << "введите данные для точки В: " << endl;
	B.Read();
	cout << "координаты точки В: " << endl;
	B.show();

	//через мейк
	point C = make_point(1.0, 1.0);
	cout << "точка С" << endl;
	C.show();

	// расстояние от А до начала координат
	cout << "расстояние от А до ( 0 ; 0 ): " << A.distance(0.0, 0.0) << endl;
	//от в до с
	cout << "расстояние от B до C: " << B.distance(C.GetX(), C.GetY()) << endl;

	return 0;
}