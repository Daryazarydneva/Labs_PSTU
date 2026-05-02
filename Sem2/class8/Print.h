#pragma once
#pragma once
#include "Object.h"
#include <string>
#include <iostream>
using namespace std;
class Print:public Object
{
protected:
	string name;//название 
	string author;//автор 
public:
	Print();
	Print(string n, string a);
	virtual ~Print();
	void Show() override;
	void Input() override;
	void HandleEvent(const TEvent& e) override;
	string GetName() const { return name; }

};

