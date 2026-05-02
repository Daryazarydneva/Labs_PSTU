#include "Print.h"
Print::Print() : name(""), author("") {};
Print::Print(string n, string a) : name(n), author(a) {};
Print::~Print() {}

void Print::Show()
{
	cout << "name " << name << ", author " << author<<endl;
}
void Print::Input()
{
	cout << "input name: "; cin >> name;
	cout << "input author: "; cin >> author;
}

void Print::HandleEvent(const TEvent& e) {
    if (e.what == evMessage && e.command == cmGetName) {
        // команда "вывести название"
        cout << "Название: " << name << endl;
    }
}