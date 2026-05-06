#include "Money.h"
#include <cmath>

Money::Money() : rubles(0), kopeks(0){}
Money::Money(long r, int k) {
    rubles = r;
    setKopeks(k);  
}
Money::~Money(){}

//норм копеек
void Money::setKopeks(int k) {
    if (k >= 100) { rubles += k / 100; kopeks = k / 100; }
    else if(k<0){
        long totalKopeks = rubles * 100 + k;
        if (totalKopeks < 0) {
            rubles = 0;
            kopeks = 0;
        }
        else {
            rubles = totalKopeks / 100;
            kopeks = totalKopeks % 100;
        }
    }
    else {
        kopeks = k;
    }
}
void Money::setMoney(long r, int k) {
    rubles = r;
    setKopeks(k);
}
//присваивание
Money& Money::operator=(const Money& other) {
    if (this == &other) return *this;
    rubles = other.rubles;
    kopeks = other.kopeks;
    return *this;
}

// Вычитание денежных сумм
Money Money::operator-(const Money& other) const {
    long total1 = rubles * 100 + kopeks;
    long total2 = other.rubles * 100 + other.kopeks;
    long result = total1 - total2;

    if (result < 0) result = 0;

    return Money(result / 100, result % 100);
}
//вычитание дробного числа
Money Money::operator-(double value) const {
    long rubPart = static_cast<long>(value);
    int kopPart = static_cast<int>((value - rubPart) * 100 + 0.5);

    Money temp(rubPart, kopPart);
    return *this - temp;
}

// Вычитание с присваиванием
Money& Money::operator-=(const Money& other) {
    *this = *this - other;
    return *this;
}
// Оператор сравнения 
bool Money::operator==(const Money& other) const {
    return (rubles == other.rubles && kopeks == other.kopeks);
}

// Оператор сравнения 
bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}
// Преобразование в double
double Money::toDouble() const {
    return rubles + kopeks / 100.0;
}
// Консольный вывод
ostream& operator<<(ostream& out, const Money& m) {
    out << m.rubles << ",";
    if (m.kopeks < 10) out << "0";
    out << m.kopeks;
    return out;
}
// Консольный ввод
istream& operator>>(istream& in, Money& m) {
    double value;
    in >> value;

    long rub = static_cast<long>(value);
    int kop = static_cast<int>((value - rub) * 100 + 0.5);

    m.setMoney(rub, kop);
    return in;
}
// Запись в файл
fstream& operator<<(fstream& fout, const Money& m) {
    fout << m.rubles << " " << m.kopeks << "\n";
    return fout;
}
// Чтение из файла
fstream& operator>>(fstream& fin, Money& m) {
    fin >> m.rubles >> m.kopeks;
    return fin;
}