#include <iostream>
#include "Header.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    // Создаём объекты разными способами
    Money a;                              // конструктор без параметров
    Money b(10, 50);                      // 10 рублей 50 копеек
    Money c(10, 50);                      // тоже 10 рублей 50 копеек
    Money d(5, 30);                       // 5 рублей 30 копеек
    Money e(b);                           // конструктор копирования (копия b)

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
    cout << "e = " << e << endl;


    // 1. Сравнение b и c (одинаковые значения)
    cout << "b == c: ";
    if (b == c) {
        cout << "ДА (10.50 == 10.50)" << endl;
    }
    else {
        cout << "НЕТ" << endl;
    }

    // 2. Сравнение b и d (разные значения)
    cout << "b == d: ";
    if (b == d) {
        cout << "ДА" << endl;
    }
    else {
        cout << "НЕТ (10.50 != 5.30)" << endl;
    }

    // 3. Оператор !=
    cout << "\nb != d: ";
    if (b != d) {
        cout << "ДА (10.50 != 5.30)" << endl;
    }
    else {
        cout << "НЕТ" << endl;
    }

    // 4. Сравнение через конструктор копирования
    cout << "\nb == e: ";
    if (b == e) {
        cout << "ДА (e — копия b)" << endl;
    }
    else {
        cout << "НЕТ" << endl;
    }

    // 5. Ввод с клавиатуры и сравнение
    Money f;
    cin >> f;
    cout << "Вы ввели: " << f << endl;

    cout << "\nСравнение b и введённого значения: ";
    if (b == f) {
        cout << "СОВПАДАЮТ" << endl;
    }
    else {
        cout << "НЕ СОВПАДАЮТ" << endl;
    }

    return 0;
}