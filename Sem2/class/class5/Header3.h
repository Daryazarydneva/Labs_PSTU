#pragma once
#include "Header.h"

class Vector {
    Object** data;
    int cap, cnt;
public:
    Vector(int n = 10) : cap(n), cnt(0) { data = new Object * [cap]; }
    ~Vector() { delete[] data; }
    void Add(Object* o) { if (cnt < cap) data[cnt++] = o; }
    void ShowAll() { for (int i = 0; i < cnt; ++i) if (data[i]) data[i]->Show(); }
};