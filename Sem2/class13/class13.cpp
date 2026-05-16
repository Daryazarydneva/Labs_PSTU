#include <iostream>
#include <deque>
#include <algorithm>
#include <numeric>
#include "Money.h"

using namespace std;

typedef deque<Money> TDeque;

// Глобальная переменная для поиска
Money searchKey;

// Прототипы функций
TDeque make_deque(int n);
void print_deque(const TDeque& d);
Money srednee(const TDeque& d);

// Предикат для сравнения с заданным значением (больше)
struct GreaterThanKey
{
    bool operator()(const Money& m)
    {
        return m > searchKey;
    }
};

// Предикат для сравнения с заданным значением (равно)
struct EqualToKey
{
    bool operator()(const Money& m)
    {
        return m == searchKey;
    }
};

// Предикат для сортировки по убыванию
struct GreaterMoney
{
    bool operator()(const Money& a, const Money& b)
    {
        return a > b;
    }
};

// Предикат для сортировки по возрастанию
struct LessMoney
{
    bool operator()(const Money& a, const Money& b)
    {
        return a < b;
    }
};

// Функция для добавления среднего арифметического к элементу
void addSrednee(Money& m, const Money& avg)
{
    m = m + avg;
}

// Функция для формирования дека
TDeque make_deque(int n)
{
    TDeque d;
    Money m;
    for (int i = 0; i < n; i++)
    {
        cout << "\nЭлемент " << i + 1 << ":" << endl;
        cin >> m;
        d.push_back(m);
    }
    return d;
}

// Функция для печати дека
void print_deque(const TDeque& d)
{
    cout << "\nСодержимое контейнера:" << endl;
    if (d.empty())
    {
        cout << "Контейнер пуст!" << endl;
        return;
    }
    for (TDeque::const_iterator i = d.begin(); i != d.end(); i++)
    {
        cout << *i << "  ";
    }
    cout << endl;
}

// Функция для вычисления среднего арифметического
Money srednee(const TDeque& d)
{
    Money sum(0, 0);
    for (TDeque::const_iterator i = d.begin(); i != d.end(); i++)
    {
        sum = sum + *i;
    }
    int n = d.size();
    if (n == 0) return Money(0, 0);
    return sum / n;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    try
    {
        int n;
        cout << "Введите количество элементов в контейнере: ";
        cin >> n;

        if (n <= 0)
        {
            cout << "Ошибка: количество элементов должно быть положительным!" << endl;
            return 1;
        }

        // Создание и заполнение контейнера
        TDeque d = make_deque(n);
        print_deque(d);

        // ========== ЗАДАНИЕ 3 ==========
        cout << "\n========== ЗАДАНИЕ 3 ==========" << endl;
        // Найти максимальный элемент
        TDeque::iterator max_it = max_element(d.begin(), d.end());
        Money maxValue = *max_it;
        cout << "Максимальный элемент: " << maxValue << endl;

        // Добавить максимальный элемент в конец контейнера
        d.push_back(maxValue);
        cout << "Максимальный элемент добавлен в конец контейнера." << endl;
        print_deque(d);

        // ========== ЗАДАНИЕ 4 ==========
        cout << "\n========== ЗАДАНИЕ 4 ==========" << endl;
        // Ввод ключа для поиска
        cout << "Введите элемент для поиска и удаления:" << endl;
        cin >> searchKey;

        // Поиск элемента с заданным ключом
        TDeque::iterator find_it = find_if(d.begin(), d.end(), EqualToKey());

        if (find_it != d.end())
        {
            cout << "Элемент " << *find_it << " найден и будет удален." << endl;
            d.erase(find_it);
            cout << "Элемент удален." << endl;
        }
        else
        {
            cout << "Элемент " << searchKey << " не найден в контейнере." << endl;
        }
        print_deque(d);

        // ========== ЗАДАНИЕ 5 ==========
        cout << "\n========== ЗАДАНИЕ 5 ==========" << endl;
        // Вычисление среднего арифметического
        Money avg = srednee(d);
        cout << "Среднее арифметическое элементов контейнера: " << avg << endl;

        // Добавление среднего арифметического к каждому элементу
        for (TDeque::iterator i = d.begin(); i != d.end(); i++)
        {
            *i = *i + avg;
        }
        cout << "Среднее арифметическое добавлено к каждому элементу." << endl;
        print_deque(d);

        // Дополнительно: сортировка по возрастанию и убыванию
        cout << "\n========== ДОПОЛНИТЕЛЬНО ==========" << endl;

        // Сортировка по возрастанию
        TDeque d_sorted_asc = d;
        sort(d_sorted_asc.begin(), d_sorted_asc.end(), LessMoney());
        cout << "\nСортировка по возрастанию:" << endl;
        print_deque(d_sorted_asc);

        // Сортировка по убыванию
        TDeque d_sorted_desc = d;
        sort(d_sorted_desc.begin(), d_sorted_desc.end(), GreaterMoney());
        cout << "\nСортировка по убыванию:" << endl;
        print_deque(d_sorted_desc);

        cout << "\nПрограмма успешно завершена!" << endl;
    }
    catch (...)
    {
        cout << "Произошла ошибка!" << endl;
    }

    return 0;
}