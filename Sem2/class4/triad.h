#pragma once
#include <iostream>
using namespace std;

class Triad {
public:
    int first, second, third;
    Triad(int f = 0, int s = 0, int t = 0) : first(f), second(s), third(t) {}

    // покомпонентное сравнение
    bool operator<(const Triad& o) const {
        if (first != o.first) return first < o.first;
        if (second != o.second) return second < o.second;
        return third < o.third;
    }
    bool operator==(const Triad& o) const {
        return first == o.first && second == o.second && third == o.third;
    }
    bool operator!=(const Triad& o) const { return !(*this == o); }
    bool operator>(const Triad& o) const { return o < *this; }
    bool operator<=(const Triad& o) const { return !(*this > o); }
    bool operator>=(const Triad& o) const { return !(*this < o); }

    friend ostream& operator<<(ostream& out, const Triad& t) {
        out << "(" << t.first << "," << t.second << "," << t.third << ")";
        return out;
    }
};