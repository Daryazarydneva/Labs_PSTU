#pragma once
#include <iostream>
#include "Error.h"
using namespace std;

const int MAX_SIZE = 30;

class Set {
private:
    int* data;
    int size;

public:
    Set();
    Set(int s);
    Set(const Set& other);
    ~Set();

    Set& operator=(const Set& other);
    int& operator[](int index);
    bool operator!=(const Set& other);

    friend bool operator<(int value, const Set& s);
    friend bool operator<(const Set& s, int value);

    void add(int value);
    void remove(int index);

    class Iterator {
    private:
        int* current;
    public:
        Iterator(int* ptr) : current(ptr) {}
        Iterator& operator++() { ++current; return *this; }
        int& operator*() { return *current; }
        bool operator!=(const Iterator& other) { return current != other.current; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }

    Iterator operator+(int n);

    int getSize() const { return size; }
    void print() const;
};