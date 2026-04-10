#pragma once
#include <iostream>
#include <string>
using namespace std;


class employee 
{
	string fullname;
	string position;
	double salary;

public:

	employee(); //без параметра 
	employee(string name, string pos, double sal); //с параметром 
	employee(const employee& other); //копирование

	~employee(); //деструктор

	string getName() const; //геттерсы
	string getPos() const;
	double getSal() const;

	void setName(const string& name);//сеттерсы
	void setPos(const string& pos);
	void setSal(double sal);

	void show();
};