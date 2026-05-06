#include "Money.h"
#include "file_work.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    const char* filename = "money.txt";

    cout << "========== VARIANT 9 ==========" << endl;
    cout << "Class Money with operations:" << endl;
    cout << "- subtraction of fractional number" << endl;
    cout << "- comparison (==, !=)" << endl;
    cout << "File operations:" << endl;
    cout << "- delete records equal to given value" << endl;
    cout << "- decrease records equal to given value by 1.50" << endl;
    cout << "- add K records after given value" << endl;
    cout << "================================" << endl;

    // ========== 1. СОЗДАНИЕ ФАЙЛА ==========
    cout << "\n[STEP 1] Creating file with initial data" << endl;

    int n = 5;  // создаем 5 записей
    Money* initialRecords = new Money[n];

    initialRecords[0] = Money(10, 50);   // 10,50
    initialRecords[1] = Money(5, 75);    // 5,75
    initialRecords[2] = Money(10, 50);   // 10,50 (дубль для удаления)
    initialRecords[3] = Money(20, 0);    // 20,00
    initialRecords[4] = Money(5, 75);    // 5,75 (дубль для уменьшения)

    cout << "Initial records:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  " << initialRecords[i] << endl;
    }

    make_file(filename);
    delete[] initialRecords;

    // ========== 2. ПЕЧАТЬ ФАЙЛА ==========
    cout << "\n[STEP 2] Printing file after creation" << endl;
    print_file(filename);

    // ========== 3. УДАЛЕНИЕ ЗАПИСЕЙ, РАВНЫХ ЗАДАННОМУ ЗНАЧЕНИЮ ==========
    cout << "\n[STEP 3] Deleting records equal to 10,50" << endl;
    Money valueToDelete(10, 50);
    delete_equal(filename, valueToDelete);

    cout << "\n[STEP 4] File after deletion" << endl;
    print_file(filename);


    // ========== 5. ДОБАВЛЕНИЕ K ЗАПИСЕЙ ПОСЛЕ ЗАДАННОГО ЗНАЧЕНИЯ ==========
    cout << "\n[STEP 7] Adding 2 records after value 20,00" << endl;
    Money valueToFind(20, 0);
    int K = 2;
    Money* newRecords = new Money[K];
    newRecords[0] = Money(100, 0);   // 100,00
    newRecords[1] = Money(200, 50);  // 200,50

    int added = add_after_value(filename, valueToFind, newRecords, K);
    delete[] newRecords;

    // Если значение не найдено, добавляем в конец
    if (added == 0) {
        cout << "Value not found. Adding to end..." << endl;
        add_end(filename, Money(999, 99));
    }

    cout << "\n[STEP 8] Final file contents" << endl;
    print_file(filename);

    // ========== 6. ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ СРАВНЕНИЯ И ВЫЧИТАНИЯ ==========
    cout << "\n[STEP 9] Demonstration of class operations" << endl;

    Money a(10, 50);
    Money b(5, 75);
    Money c(10, 50);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    cout << "a == b? " << (a == b ? "Yes" : "No") << endl;
    cout << "a == c? " << (a == c ? "Yes" : "No") << endl;
    cout << "a != b? " << (a != b ? "Yes" : "No") << endl;

    Money d = a - 3.75;  // вычитание дробного числа
    cout << "a - 3.75 = " << d << endl;

    Money e = a - b;     // вычитание денежных сумм
    cout << "a - b = " << e << endl;

    cout << "\n========== PROGRAM FINISHED ==========" << endl;

    return 0;
}