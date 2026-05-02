#pragma once
#include <iostream>
#include <string>
using namespace std;
class SetException {
public:
	virtual void print() const = 0;
	virtual ~SetException(){}
};
//превышение макс размера 
class MaxSizeError :public SetException {
public:
	void print() const override {
		cout << "max size(" << endl;
	}
};
//размер меньш 0
class NegativeIndexError : public SetException {
public:
	void print() const override {
		cout << "index < 0" << endl;
	}
};
// индекс больше текущего размера
class IndexOutOfRangeError : public SetException {
public:
    void print() const override {
        cout << "index > cur" << endl;
    }
};

//переход вправо за пределы максимального размера
class StepOutOfRangeError : public SetException {
public:
    void print() const override {
        cout << "perehod za predel vpravo" << endl;
    }
};

//удаление из пустого множества
class EmptySetError : public SetException {
public:
    void print() const override {
        cout << "dell empty" << endl;
    }
};