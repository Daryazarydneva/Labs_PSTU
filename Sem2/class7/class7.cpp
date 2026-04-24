#include <iostream>
using namespace std;

// Класс "Множество" для целых чисел
class Set {
private:
    int* data;      // массив элементов
    int size;       // текущее количество
    int capacity;   // выделенная память

    // вспомогательная функция расширения массива
    void grow() {
        int newCap = (capacity == 0) ? 1 : capacity * 2;
        int* newData = new int[newCap];
        for (int i = 0; i < size; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }

public:
    // конструктор
    Set() : data(nullptr), size(0), capacity(0) {}

    // деструктор
    ~Set() {
        delete[] data;
    }

    // конструктор копирования
    Set(const Set& other) : data(nullptr), size(other.size), capacity(other.capacity) {
        if (capacity) {
            data = new int[capacity];
            for (int i = 0; i < size; i++)
                data[i] = other.data[i];
        }
    }

    // оператор присваивания
    Set& operator=(const Set& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        if (capacity) {
            data = new int[capacity];
            for (int i = 0; i < size; i++)
                data[i] = other.data[i];
        }
        else {
            data = nullptr;
        }
        return *this;
    }

    // добавление элемента (без дубликатов)
    void add(int val) {
        // проверка на дубликат
        for (int i = 0; i < size; i++)
            if (data[i] == val) return;
        // расширение при необходимости
        if (size == capacity)
            grow();
        data[size++] = val;
    }

    // удаление по значению (если есть)
    bool remove(int val) {
        for (int i = 0; i < size; i++) {
            if (data[i] == val) {
                // сдвиг влево
                for (int j = i; j < size - 1; j++)
                    data[j] = data[j + 1];
                size--;
                return true;
            }
        }
        return false;
    }

    // оператор [] – доступ по индексу (без проверки)
    int operator[](int index) const {
        return data[index];
    }

    // оператор () – размер множества
    int operator()() const {
        return size;
    }

    // оператор – разность множеств (A - B)
    Set operator-(const Set& other) const {
        Set result;
        for (int i = 0; i < size; i++) {
            bool found = false;
            for (int j = 0; j < other.size; j++) {
                if (data[i] == other.data[j]) {
                    found = true;
                    break;
                }
            }
            if (!found)
                result.add(data[i]);
        }
        return result;
    }

    // префиксный -- : удаляет последний элемент
    Set& operator--() {
        if (size > 0)
            size--;
        return *this;
    }

    // вывод
    friend ostream& operator<<(ostream& out, const Set& s) {
        out << "{ ";
        for (int i = 0; i < s.size; i++) {
            out << s.data[i];
            if (i != s.size - 1) out << ", ";
        }
        out << " }";
        return out;
    }

    // ввод
    friend istream& operator>>(istream& in, Set& s) {
        int n;
        cout << "Количество элементов: ";
        in >> n;
        s = Set();   // очищаем
        cout << "Введите " << n << " целых чисел: ";
        for (int i = 0; i < n; i++) {
            int x;
            in >> x;
            s.add(x);
        }
        return in;
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    Set A;
    cin >> A;
    cout << "Множество A = " << A << endl;
    cout << "Размер A = " << A() << endl;

    if (A() > 0)
        cout << "Первый элемент A[0] = " << A[0] << endl;

    Set B;
    cin >> B;
    cout << "Множество B = " << B << endl;

    Set C = A - B;
    cout << "Разность A - B = " << C << endl;

    cout << "Применяем -- к A (удаляем последний элемент)" << endl;
    --A;
    cout << "A после -- = " << A << endl;

    return 0;
}