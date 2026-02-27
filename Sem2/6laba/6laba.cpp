#include <iostream>  
#include <cstring>   // для работы со строками (strlen)
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	char s[256];
	cout << "введите строку " << endl;
	gets_s(s);

	char stroka[256] = "";
	int j = 0;

	for (int i = 0; i < strlen(s); i++) {
		if ((s[i] >= 'А' && s[i] <= 'Я') ||
			(s[i] >= 'а' && s[i] <= 'я') ||
			(s[i] >= 'A' && s[i] <= 'Z') ||
			(s[i] >= 'a' && s[i] <= 'z')) {

			char c = s[i];

			if (c >= 'А' && c <= 'Я') { c = c + 32; }
			if (c >= 'A' && c <= 'Z') { c = c + 32; }

			stroka[j] = c;
			j++;

		}
	}
	stroka[j] = '\0';
	cout << stroka << endl;
	int length = strlen(stroka);
	bool isPalindrom = true;

	for (int i = 0; i < length / 2; i++)
	{
		if (stroka[i] != stroka[length - 1 - i])
		{
			isPalindrom = false;
			break;
		}
	}
	if (isPalindrom) {
		cout << "строка палиндром" << endl;
	}
	else {
		cout << "строка не является" << endl;
	}
	return 0;
}
