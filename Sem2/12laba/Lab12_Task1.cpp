// Lab12_Task1.cpp
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

typedef set<int> TSet;
typedef TSet::iterator it;

// Функция для формирования множества
TSet make_set(int n)
{
    TSet s;
    int a;
    for (int i = 0; i < n; i++)
    {
        cout << "Введите элемент " << i + 1 << ": ";
        cin >> a;
        s.insert(a);
    }
    return s;
}

// Функция для печати множества
void print_set(TSet s)
{
    cout << "Множество: { ";
    for (it i = s.begin(); i != s.end(); i++)
        cout << *i << " ";
    cout << "}" << endl;
}

// Задание 3: Найти максимальный элемент и добавить его в конец
void add_max_to_end(TSet& s)
{
    if (s.empty()) return;

    // Находим максимальный элемент (последний в отсортированном множестве)
    it max_it = --s.end();
    int max_val = *max_it;

    cout << "Максимальный элемент: " << max_val << endl;

    // Добавляем максимальный элемент в конец
    // В set нельзя добавить элемент в конкретную позицию,
    // но insert автоматически разместит его в правильном месте
    s.insert(max_val);

    cout << "Максимальный элемент добавлен в множество" << endl;
}

// Задание 4: Найти элемент с заданным ключом и удалить его
void find_and_erase(TSet& s, int key)
{
    it found = s.find(key);
    if (found != s.end())
    {
        cout << "Элемент " << key << " найден. Удаляем..." << endl;
        s.erase(found);
    }
    else
    {
        cout << "Элемент " << key << " не найден в множестве" << endl;
    }
}

// Задание 5: К каждому элементу добавить среднее арифметическое
void add_average(TSet& s)
{
    if (s.empty()) return;

    // Вычисляем среднее арифметическое
    int sum = 0;
    for (it i = s.begin(); i != s.end(); i++)
        sum += *i;

    double avg = (double)sum / s.size();
    cout << "Среднее арифметическое: " << avg << endl;

    // Создаем новое множество для результатов
    // Нельзя изменять элементы во время итерации
    TSet new_set;
    for (it i = s.begin(); i != s.end(); i++)
    {
        int new_val = *i + (int)avg;
        new_set.insert(new_val);
    }

    s = new_set;
    cout << "К каждому элементу добавлено среднее арифметическое" << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    TSet s = make_set(n);
    print_set(s);

    // Задание 3
    cout << "\n=== Задание 3: Добавить максимальный элемент в конец ===" << endl;
    add_max_to_end(s);
    print_set(s);

    // Задание 4
    cout << "\n=== Задание 4: Найти и удалить элемент ===" << endl;
    int key;
    cout << "Введите элемент для удаления: ";
    cin >> key;
    find_and_erase(s, key);
    print_set(s);

    // Задание 5
    cout << "\n=== Задание 5: Добавить к каждому элементу среднее арифметическое ===" << endl;
    add_average(s);
    print_set(s);

    return 0;
}