// eq_Half.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
//9 ВАРИАНТ
#include <iostream>
#include <cmath>
using namespace std;
int main()
//f(x) = x-1/3+sin3,6x = 0
// [0; 0,85]
{
    float a, b, c;
    float fa, fb, fc;
    double eps = 0.000001;
    a = 0;
    b = 0.85;

    while (b - a > eps)
    {
        c = (a + b) / 2;
        fa = (a - (1 / 3 + sin(3.6 * a)));
        fb = (b - (1 / 3 + sin(3.6 * b)));
        fc = (c - (1 / 3 + sin(3.6 * c)));

        if (fa * fc < 0) { b = c; }
        else if (fc * fb < 0) { a = c; }

    }
    cout << a << " " << b << endl;
}

