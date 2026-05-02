#pragma once
#include "Object.h"
#include "Print.h"
#include "Book.h"
class List
{
protected:
	Object** beg;
	int size;
	int cur;
public:
	List();
	List(int sz);
	virtual ~List();
	void Add();
	void Del();
	void Show();
	void HandleEvent(const TEvent& e);
	Object* operator[](int index);
	int GetCur() const { return cur; }

};

