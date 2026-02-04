<<<<<<< HEAD
﻿// eq_Iter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//5 вариант

#include <iostream>
#include <cmath>
using namespace std;
int main()
//f(x) = 0.25*pow(x, 3)+x-1.2502
// [0, 2]
//f'(x)=0.75*pow(x, 2)+1
{
    double x, xPrev;
    double eps = 0.000001;
    double lambda = -0.5;

    x = 1;
    xPrev = 0;

    while (abs(x - xPrev) > eps)
    {
        xPrev = x;
        x = lambda * (0.25 * pow(xPrev, 3) + xPrev - 1.2502) + xPrev;
    }
    cout<< x <<endl;
    return 0;
}

=======
﻿// eq_Iter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//5 вариант

#include <iostream>
#include <cmath>
using namespace std;
int main()
//f(x) = 0.25*pow(x, 3)+x-1.2502
// [0, 2]
//f'(x)=0.75*pow(x, 2)+1
{
    double x, xPrev;
    double eps = 0.000001;
    double lambda = -0.5;

    x = 1;
    xPrev = 0;

    while (abs(x - xPrev) > eps)
    {
        xPrev = x;
        x = lambda * (0.25 * pow(xPrev, 3) + xPrev - 1.2502) + xPrev;
    }
    cout<< x <<endl;
    return 0;
}

>>>>>>> ac2ff8e9902a0609db1464e9d85d9d2a3a3d84a0
