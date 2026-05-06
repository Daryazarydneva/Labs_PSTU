// Lab12_Task2.cpp
#include <iostream>
#include <set>
#include <algorithm>
#include "Money.h"
using namespace std;

typedef multiset<Money> TMultiSet;
typedef TMultiSet::iterator it;

// Функция для формирования мультимножества
TMultiSet make_multiset(int n)
{
    TMultiSet ms;
    Money a;
    for (int i = 0; i < n; i++)
    {
        cout << "Введите сумму " << i + 1 << " (рубли,копейки): ";
        cin >> a;
        ms.insert(a);
    }
    return ms;
}

// Функция для печати мультимножества
void print_multiset(TMultiSet ms)
{
    cout << "Мультимножество: { ";
    for (it i = ms.begin(); i != ms.end(); i++)
        cout << *i << " ";
    cout << "}" << endl;
}

// Задание 3: Найти максимальный элемент и добавить его в конец
void add_max_to_end(TMultiSet& ms)
{
    if (ms.empty()) return;

    // Находим максимальный элемент
    it max_it = --ms.end();
    Money max_val = *max_it;

    cout << "Максимальный элемент: " << max_val << endl;

    // Добавляем копию максимального элемента
    ms.insert(max_val);

    cout << "Максимальный элемент добавлен в мультимножество" << endl;
}

// Задание 4: Найти элемент с заданным ключом и удалить одно его вхождение
void find_and_erase_one(TMultiSet& ms, Money key)
{
    it found = ms.find(key);
    if (found != ms.end())
    {
        cout << "Элемент " << key << " найден. Удаляем..." << endl;
        ms.erase(found);  // Удаляет только один элемент
    }
    else
    {
        cout << "Элемент " << key << " не найден в мультимножестве" << endl;
    }
}

// Задание 5: К каждому элементу добавить среднее арифметическое
void add_average(TMultiSet& ms)
{
    if (ms.empty()) return;

    // Вычисляем сумму всех элементов
    Money sum(0, 0);
    for (it i = ms.begin(); i != ms.end(); i++)
        sum = sum + *i;

    // Вычисляем среднее арифметическое
    Money avg = sum / ms.size();
    cout << "Среднее арифметическое: " << avg << endl;

    // Создаем новое мультимножество для результатов
    TMultiSet new_ms;
    for (it i = ms.begin(); i != ms.end(); i++)
    {
        Money new_val = *i + avg;
        new_ms.insert(new_val);
    }

    ms = new_ms;
    cout << "К каждому элементу добавлено среднее арифметическое" << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    TMultiSet ms = make_multiset(n);
    print_multiset(ms);

    // Задание 3
    cout << "\n=== Задание 3: Добавить максимальный элемент ===" << endl;
    add_max_to_end(ms);
    print_multiset(ms);

    // Задание 4
    cout << "\n=== Задание 4: Найти и удалить элемент ===" << endl;
    Money key;
    cout << "Введите сумму для удаления (рубли,копейки): ";
    cin >> key;
    find_and_erase_one(ms, key);
    print_multiset(ms);

    // Задание 5
    cout << "\n=== Задание 5: Добавить к каждому элементу среднее арифметическое ===" << endl;
    add_average(ms);
    print_multiset(ms);

    return 0;
}