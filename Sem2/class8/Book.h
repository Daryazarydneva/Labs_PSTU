#pragma once
#include "Print.h"
class Book : public Print
{
protected:
	int pages;
	string publisher;
public:
	Book();
	Book(string n, string a, int p, string pub);
	~Book();
	void Show() override;
	void Input() override;
	void HandleEvent(const TEvent& e) override;
};

