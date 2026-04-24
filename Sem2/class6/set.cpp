#include "Set.h"
#include <algorithm>  // для std::copy
using namespace std;

// конструктор без параметров
Set::Set() : data(nullptr), size(0), capacity(0) {}

// конструктор с указанием начальной ёмкости
Set::Set(int cap) : data(nullptr), size(0), capacity(cap) {
    if (capacity > 0)
        data = new int[capacity];
}


// деструктор
Set::~Set() {
    delete[] data;
}

// вспомогательная функция изменения ёмкости
void Set::resize(int new_capacity) {
    int* new_data = new int[new_capacity];
    // копируем старые элементы
    for (int i = 0; i < size; ++i)
        new_data[i] = data[i];
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

// операция присваивания
Set& Set::operator=(const Set& other) {
    if (this == &other) return *this; // самоприсваивание
    delete[] data;
    size = other.size;
    capacity = other.capacity;
    if (capacity > 0) {
        data = new int[capacity];
        copy(other.data, other.data + size, data);
    }
    else {
        data = nullptr;
    }
    return *this;
}

// добавление элемента (без дубликатов)
void Set::add(int value) {
    // сначала проверим, есть ли уже такой элемент
    for (int i = 0; i < size; ++i)
        if (data[i] == value)
            return; // уже есть – ничего не делаем

    // если места нет, увеличиваем ёмкость
    if (size == capacity) {
        int new_cap = (capacity == 0) ? 1 : capacity * 2;
        resize(new_cap);
    }
    data[size++] = value;
}

// удаление элемента
void Set::remove(int value) {
    int index = -1;
    for (int i = 0; i < size; ++i)
        if (data[i] == value) {
            index = i;
            break;
        }
    if (index == -1) return; // не найдено
    // сдвигаем элементы влево
    for (int i = index; i < size - 1; ++i)
        data[i] = data[i + 1];
    --size;
}

// проверка принадлежности
bool Set::contains(int value) const {
    for (int i = 0; i < size; ++i)
        if (data[i] == value)
            return true;
    return false;
}

// доступ по индексу (без проверки границ – для простоты)
int& Set::operator[](int index) {
    return data[index];
}
const int& Set::operator[](int index) const {
    return data[index];
}

// операция неравенства двух множеств
bool Set::operator!=(const Set& other) const {
    if (size != other.size) return true;
    // поочерёдно сравниваем элементы (порядок может быть разный)
    // поэтому для каждого элемента одного множества ищем его в другом
    for (int i = 0; i < size; ++i) {
        if (!other.contains(data[i]))
            return true;
    }
    return false;
}

// операция "<" число (принадлежность)
bool operator<(int value, const Set& s) {
    return s.contains(value);
}

// вывод множества в поток
ostream& operator<<(ostream& out, const Set& s) {
    out << "{ ";
    for (int i = 0; i < s.size; ++i) {
        out << s.data[i];
        if (i != s.size - 1) out << ", ";
    }
    out << " }";
    return out;
}

// ввод множества из потока: сначала количество, затем элементы
istream& operator>>(istream& in, Set& s) {
    int n;
    cout << "Введите количество элементов: ";
    in >> n;
    s = Set(n);   // создаём новое множество с ёмкостью n
    cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; ++i) {
        int x;
        in >> x;
        s.add(x);
    }
    return in;
}
