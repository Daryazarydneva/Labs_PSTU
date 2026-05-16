#pragma once
#include <iostream>
#include <string>
using namespace std;

class Money
{
private:
    long rubles;   // рубли
    int kopecks;   // копейки

public:
    // Конструкторы
    Money();
    Money(long r, int k);
    Money(const Money& other);
    ~Money();

    // Селекторы
    long getRubles() const { return rubles; }
    int getKopecks() const { return kopecks; }

    // Модификаторы
    void setRubles(long r) { rubles = r; }
    void setKopecks(int k) { kopecks = k; }

    // Перегруженные операции
    Money& operator=(const Money& other);
    Money operator+(const Money& other) const;
    Money operator-(const Money& other) const;
    Money operator/(int divisor) const;
    Money operator*(double factor) const;
    bool operator>(const Money& other) const;
    bool operator<(const Money& other) const;
    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;

    // Операции ввода-вывода
    friend istream& operator>>(istream& in, Money& m);
    friend ostream& operator<<(ostream& out, const Money& m);
};