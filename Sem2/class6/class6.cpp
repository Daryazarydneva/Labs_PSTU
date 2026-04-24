#include <windows.h>
#include "Set.h"
#include <iostream>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
   
    setlocale(LC_ALL, "Russian");  // для русских сообщений (Windows)

    // 1. Создание множества и ввод
    Set A;
    cin >> A;                // используем перегруженный >>
    cout << "Множество A: " << A << endl;

    // 2. Проверка операции [] и итератора
    if (A.getSize() > 0) {
        cout << "Первый элемент через [0]: " << A[0] << endl;
    }

    // 3. Проверка операции + n (итератор) – переход вправо на n
    int n;
    cout << "Введите n для перехода итератора: ";
    cin >> n;
    Iterator it = A.begin();
    if (n < A.getSize()) {
        Iterator it2 = it + n;   // смещение вправо
        cout << "Элемент с номером " << n << " (начиная с 0): " << *it2 << endl;
    }
    else {
        cout << "n превышает размер множества" << endl;
    }

    // 4. Проверка операции "число < множество"
    int val;
    cout << "Введите число для проверки принадлежности: ";
    cin >> val;
    if (val < A)   // используем перегруженный operator<
        cout << val << " принадлежит множеству" << endl;
    else
        cout << val << " НЕ принадлежит множеству" << endl;

    // 5. Проверка операции != (сравнение двух множеств)
    Set B;
    cout << "\nВведите другое множество B:" << endl;
    cin >> B;
    cout << "B = " << B << endl;
    if (A != B)
        cout << "Множества A и B различны" << endl;
    else
        cout << "Множества A и B равны" << endl;

    // 6. Демонстрация добавления и удаления
    cout << "\nДобавим 100 в A" << endl;
    A.add(100);
    cout << "A = " << A << endl;
    cout << "Удалим первый элемент из A" << endl;
    if (A.getSize() > 0) A.remove(A[0]);
    cout << "A = " << A << endl;

    return 0;
}