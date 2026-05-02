#include "List.h"
#include <iostream>
using namespace std;

List::List() : beg(nullptr), size(0), cur(0) {}
List::List(int sz): size(sz), cur(0){
	beg = new Object * [size];
}

List::~List(){

	for (int i = 0; i < cur; ++i)
		delete beg[i];
	delete[] beg;
}

void List::Add() {
	if (cur >= size) {
		cout << "gruppa zapolnena"<<endl;
		return;
	}
	cout << "viberite tip:\n1. Publisher\n2. Book\n.>";
	int choise;
	cin >> choise;
	Object* p = nullptr;
	if (choise == 1) {
		p = new Print();
		p->Input();
	}
	else if (choise == 2) {
		p = new Book();
		p->Input();
	}
	else {
		cout << "error" << endl;
		return;
	}
	beg[cur++] = p;
	cout << "object add" << endl;

}

void List::Del() {
	if (cur = 0) {
		cout << "gruppa pusta, nechego ydalyat." << endl;
		return;
	}
	cur--;
	delete beg[cur];
	beg[cur] = nullptr;
	cout << "last elemen delete" << endl;

}

void List::Show() {
	if (cur == 0) {
		cout << "empty group" << endl;
		return;
	}
	for (int i = 0; i < cur; ++i)
	{
		cout << i + 1 << ". ";
		beg[i]->Show();
	}
}

void List::HandleEvent(const TEvent& e) {
	for (int i = 0; i < cur; ++i) {
		beg[i]->HandleEvent(e);
	}
}
Object* List::operator[](int index) {
	if (index < 0 || index >= cur) return nullptr;
	return beg[index];
}
