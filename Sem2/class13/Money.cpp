#include "Money.h"

// Конструктор без параметров
Money::Money()
{
    rubles = 0;
    kopecks = 0;
}

// Конструктор с параметрами
Money::Money(long r, int k)
{
    rubles = r;
    kopecks = k;
    // Нормализация: если копеек больше 99, переводим в рубли
    if (kopecks >= 100)
    {
        rubles += kopecks / 100;
        kopecks %= 100;
    }
    if (kopecks < 0)
    {
        long rubs_from_kop = (kopecks / 100) - 1;
        rubles += rubs_from_kop;
        kopecks = kopecks - rubs_from_kop * 100;
    }
}

// Конструктор копирования
Money::Money(const Money& other)
{
    rubles = other.rubles;
    kopecks = other.kopecks;
}

// Деструктор
Money::~Money() {}

// Оператор присваивания
Money& Money::operator=(const Money& other)
{
    if (this != &other)
    {
        rubles = other.rubles;
        kopecks = other.kopecks;
    }
    return *this;
}

// Оператор сложения
Money Money::operator+(const Money& other) const
{
    long total_kopecks = (rubles * 100 + kopecks) + (other.rubles * 100 + other.kopecks);
    Money result;
    result.rubles = total_kopecks / 100;
    result.kopecks = total_kopecks % 100;
    return result;
}

// Оператор вычитания
Money Money::operator-(const Money& other) const
{
    long total_kopecks = (rubles * 100 + kopecks) - (other.rubles * 100 + other.kopecks);
    if (total_kopecks < 0)
    {
        Money result(0, 0);
        return result;
    }
    Money result;
    result.rubles = total_kopecks / 100;
    result.kopecks = total_kopecks % 100;
    return result;
}

// Оператор деления на целое число
Money Money::operator/(int divisor) const
{
    if (divisor == 0) return Money(0, 0);
    long total_kopecks = rubles * 100 + kopecks;
    long result_kopecks = total_kopecks / divisor;
    Money result;
    result.rubles = result_kopecks / 100;
    result.kopecks = result_kopecks % 100;
    return result;
}

// Оператор умножения на дробное число
Money Money::operator*(double factor) const
{
    long total_kopecks = rubles * 100 + kopecks;
    double result_kopecks = total_kopecks * factor;
    Money result;
    result.rubles = (long)result_kopecks / 100;
    result.kopecks = (int)((long)result_kopecks % 100);
    return result;
}

// Оператор сравнения "больше"
bool Money::operator>(const Money& other) const
{
    long this_kop = rubles * 100 + kopecks;
    long other_kop = other.rubles * 100 + other.kopecks;
    return this_kop > other_kop;
}

// Оператор сравнения "меньше"
bool Money::operator<(const Money& other) const
{
    long this_kop = rubles * 100 + kopecks;
    long other_kop = other.rubles * 100 + other.kopecks;
    return this_kop < other_kop;
}

// Оператор сравнения "равно"
bool Money::operator==(const Money& other) const
{
    return (rubles == other.rubles && kopecks == other.kopecks);
}

// Оператор сравнения "не равно"
bool Money::operator!=(const Money& other) const
{
    return !(*this == other);
}

// Оператор ввода
istream& operator>>(istream& in, Money& m)
{
    cout << "Введите рубли: ";
    in >> m.rubles;
    cout << "Введите копейки: ";
    in >> m.kopecks;
    return in;
}

// Оператор вывода
ostream& operator<<(ostream& out, const Money& m)
{
    out << m.rubles << ",";
    if (m.kopecks < 10) out << "0";
    out << m.kopecks << " руб.";
    return out;
}