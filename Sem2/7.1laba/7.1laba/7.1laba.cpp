#include <iostream>
using namespace std;

// Функция а) для сложения десятичных дробей (тип double)
double dr(double a, double b) {
    return a + b;
    

}

double dr(int chisl1, int znam1, int chisl2, int znam2)
{
    int drob = chisl1 * znam2 + chisl2 * znam1;
    int drob2 = znam1 * znam2;
    return (double)drob/drob2;

}

int main()
{
    setlocale(LC_ALL, "Russian");
    double a1, b1;
    cout << "введите десятичные дроби";
    cin >> a1;
    cin >> b1;
    cout<<"результат " << dr(a1, b1)<<endl;
    
    double ch1, zn1, ch2, zn2;
    cout << "введите числитель и знаменатель";
    cin >> ch1 >> zn1;
    cout << "введите числитель и знаменатель 2";
    cin >> ch2 >> zn2;
    cout << "результат " << dr(ch1, zn1, ch2, zn2);

    return 0;
}
