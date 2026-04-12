#pragma once
#include <iostream>
using namespace std;

class Money {
private:
    long rub;   // рубли
    int kop;    // копейки (0..99)

public:
    // Конструкторы
    Money();                         // без параметров
    Money(long r, int k);            // с параметрами
    Money(const Money& other);       // копирования

    // Деструктор
    ~Money();

    // Селекторы (геттеры)
    long getRub() const;
    int getKop() const;

    // Модификаторы (сеттеры)
    void setRub(long r);
    void setKop(int k);

    // Перегрузка оператора присваивания
    Money& operator=(const Money& other);

    //операция сравнения
    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;

    // Дружественные функции ввода/вывода
    friend istream& operator>>(istream& in, Money& m);
    friend ostream& operator<<(ostream& out, const Money& m);
};
