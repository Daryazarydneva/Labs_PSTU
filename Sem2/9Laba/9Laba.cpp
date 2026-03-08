#include <iostream>      
#include <fstream>       
#include <string>        
#include <windows.h> 

using namespace std;

int main() {
    setlocale(LC_CTYPE, "rus");
     
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    //копирование строк из ф1 в ф2 

    ifstream inputFile("F1.txt");
    ofstream outputFile("F2.txt");

    string line;
    int spaceCount;
    int lineNumber = 0;

    while (getline(inputFile, line)) {
        spaceCount = 0;

        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ' ') {
                spaceCount++;
            }
        }
        if (spaceCount == 0 && line.length() > 0) {
            outputFile << line << endl;
            cout << ++lineNumber << ": " << line << endl;
        }
    }
    inputFile.close();   
    outputFile.close();

    ifstream fileF2("F2.txt");
    string longestWord; // Переменная для хранения самого длинного слова
    string currentWord; // Переменная для хранения текущего читаемого слова
    string currentLine; // Переменная для хранения текущей строки из файла

    while (getline(fileF2, currentLine)) {
        currentWord = "";
        for (int i = 0; i <= currentLine.length(); i++) {
            if (i == currentLine.length() || currentLine[i] == ' ') {
                if (currentLine.length() > 0) {
                    if (currentWord.length() > longestWord.length()) {
                        longestWord = currentWord;
                    }
                    currentWord = "";
                }
            }
            else
            {
                currentWord += currentLine[i];
            }
        }

    }
    fileF2.close();
    
    cout << "\nРезультаты поиска в файле F2:" << endl;
    if (longestWord.length() > 0) {  
        cout << "Самое длинное слово: " << longestWord << endl;
        cout << "Длина слова: " << longestWord.length() << " символов" << endl;
    }
    else {
        cout << "Файл F2 пуст или не содержит слов" << endl;
    }

    return 0;  
}