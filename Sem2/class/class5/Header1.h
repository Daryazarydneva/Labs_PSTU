#pragma once
#include "Header.h"
#include <iostream>
using namespace std;

class Triad : public Object {
public:
    int a, b, c;
    Triad(int x = 0, int y = 0, int z = 0) : a(x), b(y), c(z) {}
    virtual void Show() const override {
        cout << "Triad(" << a << "," << b << "," << c << ")" << endl;
    }
};