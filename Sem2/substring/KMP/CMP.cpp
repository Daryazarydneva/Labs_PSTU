#include <iostream>
#include <string>
using namespace std;

int KMP_search(const string& str, const string& templ) {
    int strlen = str.length();
    int templen = templ.length();

    if (strlen == 0 || templen == 0)
        return -1;

    if (templen > strlen)
        return -1;

    // Вычисление префикс-функции
    int* d = new int[templen];
    int i = 0;
    int j = -1;
    d[0] = -1;

    while (i < templen - 1) {
        while ((j >= 0) && (templ[j] != templ[i])) {
            j = d[j];
        }
        ++i;
        ++j;
        if (templ[i] == templ[j]) {
            d[i] = d[j];
        }
        else {
            d[i] = j;
        }
    }

    // Поиск строки
    i = 0;
    j = 0;
    while (i < strlen && j < templen) {
        while ((j >= 0) && (templ[j] != str[i])) {
            j = d[j];
        }
        ++i;
        ++j;
    }

    delete[] d;

    // Если совпадение есть - возвращаем позицию, если нет - -1
    if (j == templen) {
        return i - j;
    }
    else {
        return -1;
    }
}

// Функция для демонстрации работы префикс-функции
void printPrefixFunction(const string& templ) {
    int templen = templ.length();
    int* d = new int[templen];
    int i = 0;
    int j = -1;
    d[0] = -1;

    while (i < templen - 1) {
        while ((j >= 0) && (templ[j] != templ[i])) {
            j = d[j];
        }
        ++i;
        ++j;
        if (templ[i] == templ[j]) {
            d[i] = d[j];
        }
        else {
            d[i] = j;
        }
    }

    cout << "Префикс-функция для \"" << templ << "\": ";
    for (int k = 0; k < templen; k++) {
        cout << d[k] << " ";
    }
    cout << endl;

    delete[] d;
}

int main() {
    setlocale(LC_ALL, "ru");
    string text, pattern;
    int choice;

    cout << "\nВведите текст: ";
    getline(cin, text);

    cout << "Введите образец для поиска: ";
    getline(cin, pattern);

    cout << endl;

  
    int result = KMP_search(text, pattern);

    if (result != -1) {
        cout << "Образец найден!" << endl;
        cout << "Позиция: " << result << endl;
        
    }
    else {
        cout << "Образец не найден!" << endl;
    }

    return 0;
}