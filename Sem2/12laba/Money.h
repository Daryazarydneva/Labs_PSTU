// Money.h
#pragma once
#include <iostream>
using namespace std;

class Money
{
private:
    long rubles;    // рубли
    int kopecks;    // копейки

public:
    // Конструкторы
    Money() : rubles(0), kopecks(0) {}
    Money(long r, int k) : rubles(r), kopecks(k)
    {
        // Нормализация копеек
        if (kopecks >= 100)
        {
            rubles += kopecks / 100;
            kopecks %= 100;
        }
        if (kopecks < 0)
        {
            rubles += kopecks / 100 - 1;
            kopecks = 100 + (kopecks % 100);
            if (kopecks == 100) kopecks = 0;
        }
    }
    Money(const Money& m) : rubles(m.rubles), kopecks(m.kopecks) {}

    // Селекторы
    long get_rubles() const { return rubles; }
    int get_kopecks() const { return kopecks; }

    // Модификаторы
    void set_rubles(long r) { rubles = r; }
    void set_kopecks(int k)
    {
        kopecks = k;
        if (kopecks >= 100)
        {
            rubles += kopecks / 100;
            kopecks %= 100;
        }
    }

    // Операторы сравнения для использования в set/multiset
    bool operator<(const Money& other) const
    {
        if (rubles != other.rubles)
            return rubles < other.rubles;
        return kopecks < other.kopecks;
    }

    bool operator>(const Money& other) const
    {
        if (rubles != other.rubles)
            return rubles > other.rubles;
        return kopecks > other.kopecks;
    }

    bool operator==(const Money& other) const
    {
        return rubles == other.rubles && kopecks == other.kopecks;
    }

    bool operator!=(const Money& other) const
    {
        return !(*this == other);
    }

    // Оператор сложения
    Money operator+(const Money& other) const
    {
        long total_kopecks = rubles * 100 + kopecks + other.rubles * 100 + other.kopecks;
        return Money(total_kopecks / 100, total_kopecks % 100);
    }

    // Оператор деления на целое число (для среднего)
    Money operator/(int divisor) const
    {
        long total_kopecks = rubles * 100 + kopecks;
        total_kopecks /= divisor;
        return Money(total_kopecks / 100, total_kopecks % 100);
    }

    // Ввод/вывод
    friend ostream& operator<<(ostream& out, const Money& m)
    {
        out << m.rubles << ",";
        if (m.kopecks < 10) out << "0";
        out << m.kopecks;
        return out;
    }

    friend istream& operator>>(istream& in, Money& m)
    {
        char comma;
        in >> m.rubles >> comma >> m.kopecks;
        return in;
    }
};