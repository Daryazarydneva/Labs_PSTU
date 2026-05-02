#include "Set.h"
#include <iostream>
using namespace std;


Set::Set() {
    size = 0;
    data = nullptr;
}


Set::Set(int s) {
    if (s > MAX_SIZE) {
        throw MaxSizeError();           
    }
    size = s;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
}


Set::Set(const Set& other) {
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}


Set::~Set() {
    delete[] data;
}


Set& Set::operator=(const Set& other) {
    if (this == &other) return *this;
    delete[] data;
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
    return *this;
}


int& Set::operator[](int index) {
    if (index < 0) {
        throw NegativeIndexError();     
    }
    if (index >= size) {
        throw IndexOutOfRangeError();   
    }
    return data[index];
}


bool Set::operator!=(const Set& other) {
    if (size != other.size) return true;
    for (int i = 0; i < size; i++) {
        if (data[i] != other.data[i]) return true;
    }
    return false;
}




Set::Iterator Set::operator+(int n) {
    if (n > MAX_SIZE) {
        throw StepOutOfRangeError();    
    }

    if (n >= size) {
        return end();
    }
    return Iterator(data + n);
}


void Set::add(int value) {
    // Проверяем, есть ли уже такой элемент
    for (int i = 0; i < size; i++) {
        if (data[i] == value) return;   // уже есть
    }

    // Увеличиваем размер
    int* newData = new int[size + 1];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    newData[size] = value;
    delete[] data;
    data = newData;
    size++;
}


void Set::remove(int index) {
    if (size == 0) {
        throw EmptySetError();          
    }
    if (index < 0 || index >= size) {
        throw IndexOutOfRangeError();   
    }

    int* newData = new int[size - 1];
    for (int i = 0, j = 0; i < size; i++) {
        if (i != index) {
            newData[j++] = data[i];
        }
    }
    delete[] data;
    data = newData;
    size--;
}


void Set::print() const {
    if (size == 0) {
        cout << "Множество пустое {}" << endl;
        return;
    }
    cout << "{ ";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " }" << endl;
}
bool operator<(int value, const Set& s) {
    for (int i = 0; i < s.size; i++) {
        if (s.data[i] == value) return true;
    }
    return false;
}

bool operator<(const Set& s, int value) {
    for (int i = 0; i < s.size; i++) {
        if (s.data[i] == value) return true;
    }
    return false;
}