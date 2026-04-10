#include "Employee.h"

employee::employee()
{
	fullname = "";
	position = "";
	salary = 0;
	cout << "Вызван конструктор без параметров , объект"<< this;
}

employee::employee(string name, string pos, double sal)
{
	fullname = name;
	position = pos;
	salary = sal;
	cout << "Вызван конструктор с параметрами , объект" << this;
}

employee::employee(const employee& other)
{
	fullname = other.fullname;
	position = other.position;
	salary = other.salary;
	cout << "Вызван конструктор копирования , объект " << this;

}

employee::~employee()
{
	cout << "вызван деструктор для объектов, " << this;
}

string employee::getName() const { return fullname; }
string employee::getPos() const { return position; }
double employee::getSal() const { return salary; }

void employee::setName(const string& name) { fullname = name; }
void employee::setPos(const string& pos) { position = pos; }
void employee::setSal(double sal) { salary = sal; }

void employee::show()
{
	cout << "ФИО: " << fullname << endl <<
		"должность: " << position << endl <<
		"зарплата: " << salary;

}