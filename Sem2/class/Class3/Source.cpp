#include "Header.h"

Money::Money() : rub(0), kop(0) {}

Money::Money(long r, int k) : rub(r), kop(k) {
    // Нормализация копеек (приводим к диапазону 0..99)
    if (kop >= 100) {
        rub += kop / 100;
        kop %= 100;
    }
    else if (kop < 0) {
        long need = (-kop + 99) / 100;
        rub -= need;
        kop += need * 100;
    }
}

Money::Money(const Money& other) : rub(other.rub), kop(other.kop) {}

Money::~Money() {}


long Money::getRub() const { return rub; }
int Money::getKop() const { return kop; }


void Money::setRub(long r) { rub = r; }

void Money::setKop(int k) {
    kop = k;
    if (kop >= 100) {
        rub += kop / 100;
        kop %= 100;
    }
    else if (kop < 0) {
        long need = (-kop + 99) / 100;
        rub -= need;
        kop += need * 100;
    }
}


Money& Money::operator=(const Money& other) {
    if (this != &other) {
        rub = other.rub;
        kop = other.kop;
    }
    return *this;
}




bool Money::operator==(const Money& other) const {
    return (rub == other.rub) && (kop == other.kop);
}


bool Money::operator!=(const Money& other) const {
    return !(*this == other);  
}


istream& operator>>(istream& in, Money& m) {
    cout << "Введите рубли и копейки: ";
    in >> m.rub >> m.kop;
    // Нормализация
    if (m.kop >= 100) {
        m.rub += m.kop / 100;
        m.kop %= 100;
    }
    else if (m.kop < 0) {
        long need = (-m.kop + 99) / 100;
        m.rub -= need;
        m.kop += need * 100;
    }
    return in;
}

ostream& operator<<(ostream& out, const Money& m) {
    out << m.rub << ",";
    if (m.kop < 10) out << "0";
    out << m.kop;
    return out;
}