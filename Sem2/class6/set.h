#pragma once
#include <iostream>
using namespace std;


class Iterator {
    friend class Set;  // множество может создавать итераторы
private:
    int* elem;         // указатель на текущий элемент
public:
    Iterator() : elem(nullptr) {}
    Iterator(int* p) : elem(p) {}
    Iterator(const Iterator& it) : elem(it.elem) {}

    // операции сравнения итераторов
    bool operator==(const Iterator& it) const { return elem == it.elem; }
    bool operator!=(const Iterator& it) const { return elem != it.elem; }

    // переход к следующему элементу (префиксный)
    Iterator& operator++() {
        ++elem;
        return *this;
    }
    // постфиксный инкремент
    Iterator operator++(int) {
        Iterator tmp = *this;
        ++elem;
        return tmp;
    }

    // переход вправо на n элементов (для варианта 9)
    Iterator operator+(int n) const {
        return Iterator(elem + n);
    }

    // разыменование – доступ к текущему элементу
    int& operator*() const { return *elem; }
};

// Класс-контейнер "Множество"
class Set {
private:
    int* data;         // динамический массив элементов
    int size;          // текущее количество элементов
    int capacity;      // выделенная ёмкость

    // вспомогательная функция для изменения размера массива
    void resize(int new_capacity);

public:
    // конструкторы и деструктор
    Set();                               // без параметров
    explicit Set(int cap);               // с указанием начальной ёмкости
    ~Set();                              // деструктор

    // операция присваивания
    Set& operator=(const Set& other);

    // добавление элемента 
    void add(int value);
    // удаление элемента 
    void remove(int value);
    // проверка принадлежности числа множеству
    bool contains(int value) const;

    // операции доступа:
    int& operator[](int index);         
    const int& operator[](int index) const;

    // проверка на неравенство двух множеств
    bool operator!=(const Set& other) const;

    friend bool operator<(int value, const Set& s);

    // ввод/вывод через потоки (дружественные функции)
    friend ostream& operator<<(ostream& out, const Set& s);
    friend istream& operator>>(istream& in, Set& s);

    // получение размера
    int getSize() const { return size; }
    // доступ к данным для итератора (не рекомендуется, но нужно)
    int* getData() const { return data; }

    // итераторы: начало и конец
    Iterator begin() const { return Iterator(data); }
    Iterator end() const { return Iterator(data + size); }
};
