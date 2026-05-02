#include "Book.h"
Book::Book() :Print(), pages(0), publisher(""){}
Book::Book(string n, string a, int p, string pub): 
	Print(n, a), pages(p), publisher(pub){ }
Book::~Book(){}

void Book::Show() {
	Print::Show();
	cout << "pages: " << " publisher: " << publisher << endl;
}

void Book::Input() {
	Print::Input();
	cout << "count pages: "; cin >> pages;
	cout << "publisher: "; cin >> publisher;

}

void Book::HandleEvent(const TEvent& e) {
	Print::HandleEvent(e);
}
