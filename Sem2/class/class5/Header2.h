#pragma once
#include "Header1.h"

class Time : public Triad {
public:
    Time(int h = 0, int m = 0, int s = 0) : Triad(h, m, s) {}
    virtual void Show() const override {
        cout << (a < 10 ? "0" : "") << a << ":" << (b < 10 ? "0" : "") << b << ":"
            << (c < 10 ? "0" : "") << c << endl;
    }
};