// Lab12_Task3.cpp
#include <iostream>
#include <map>
#include <algorithm>
#include "Money.h"
using namespace std;

typedef map<int, Money> TMap;
typedef TMap::iterator it;

// Функция для формирования словаря
TMap make_map(int n)
{
    TMap m;
    Money val;
    for (int i = 0; i < n; i++)
    {
        cout << "Введите значение для ключа " << i << " (рубли,копейки): ";
        cin >> val;
        m[i] = val;  // ключ - индекс, значение - Money
    }
    return m;
}

// Функция для печати словаря
void print_map(TMap m)
{
    cout << "Словарь:" << endl;
    for (it i = m.begin(); i != m.end(); i++)
        cout << "  ключ " << i->first << " -> " << i->second << endl;
}

// Задание 3: Найти максимальный элемент (по значению) и добавить его в конец
void add_max_to_end(TMap& m)
{
    if (m.empty()) return;

    // Находим максимальный ключ (последний в отсортированном map)
    it max_key_it = --m.end();
    int max_key = max_key_it->first;
    Money max_val = max_key_it->second;

    // Находим максимальное значение (перебором)
    it max_val_it = m.begin();
    for (it i = m.begin(); i != m.end(); i++)
    {
        if (i->second > max_val_it->second)
            max_val_it = i;
    }

    cout << "Максимальный элемент: ключ " << max_val_it->first
        << ", значение " << max_val_it->second << endl;

    // Добавляем новую пару с новым ключом (существующий максимальный ключ + 1)
    int new_key = max_key + 1;
    m[new_key] = max_val_it->second;

    cout << "Максимальный элемент добавлен с ключом " << new_key << endl;
}

// Задание 4: Найти элемент с заданным ключом и удалить его
void find_and_erase(TMap& m, int key)
{
    it found = m.find(key);
    if (found != m.end())
    {
        cout << "Элемент с ключом " << key << " найден. Значение: "
            << found->second << ". Удаляем..." << endl;
        m.erase(found);
    }
    else
    {
        cout << "Элемент с ключом " << key << " не найден в словаре" << endl;
    }
}

// Задание 5: К каждому значению добавить среднее арифметическое всех значений
void add_average(TMap& m)
{
    if (m.empty()) return;

    // Вычисляем сумму всех значений
    Money sum(0, 0);
    int count = 0;
    for (it i = m.begin(); i != m.end(); i++)
    {
        sum = sum + i->second;
        count++;
    }

    // Вычисляем среднее арифметическое
    Money avg = sum / count;
    cout << "Среднее арифметическое значений: " << avg << endl;

    // Добавляем среднее к каждому значению
    for (it i = m.begin(); i != m.end(); i++)
    {
        i->second = i->second + avg;
    }

    cout << "К каждому значению добавлено среднее арифметическое" << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    TMap m = make_map(n);
    print_map(m);

    // Задание 3
    cout << "\n=== Задание 3: Добавить максимальный элемент ===" << endl;
    add_max_to_end(m);
    print_map(m);

    // Задание 4
    cout << "\n=== Задание 4: Найти и удалить элемент по ключу ===" << endl;
    int key;
    cout << "Введите ключ для удаления: ";
    cin >> key;
    find_and_erase(m, key);
    print_map(m);

    // Задание 5
    cout << "\n=== Задание 5: Добавить к каждому значению среднее арифметическое ===" << endl;
    add_average(m);
    print_map(m);

    return 0;
}