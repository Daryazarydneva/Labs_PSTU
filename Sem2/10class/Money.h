#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Money
{
	long rubles;
	int kopeks;

public:
	Money();
	Money(long r, int k);

	~Money();

	long getRubles() const {return rubles;}
	int gerKopeks() const { return kopeks; }

	void setRubles(long r);
	void setKopeks(int k);
	void setMoney(long r, int k);

	Money& operator = (const Money& other);
	
	Money operator-(const Money& other) const;// вычитание денежных сумм
	Money operator-(double value) const; // вычитание дробного числа
	Money& operator-=(const Money& other);// вычитание с присваиванием

	bool operator==(const Money& other) const;
	bool operator!=(const Money& other) const;

	double toDouble() const;

	// Для консоли
	friend ostream& operator<<(ostream& out, const Money& m);
	friend istream& operator>>(istream& in, Money& m);

	// Для файловых потоков
	friend fstream& operator<<(fstream& fout, const Money& m);
	friend fstream& operator>>(fstream& fin, Money& m);
};

