#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

// Структура узла стека
struct Node {
    int data;        // Данные узла
    Node* next;      // Указатель на следующий элемент
};

// 1. Функция создания пустого списка (стека)
Node* createList() {
    return nullptr;  // Пустой список 
}

// 2. Функция добавления элемента в стек (на вершину)
Node* push(Node* top, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = top;
    cout << "Добавлен элемент: " << value << endl;
    return newNode;  // Новый элемент становится вершиной стека
}

// 3. Функция удаления элемента из стека (с вершины)
Node* pop(Node* top, int& deletedValue) {
    if (top == nullptr) {
        cout << "Ошибка: стек пуст!" << endl;
        deletedValue = -1;
        return nullptr;
    }

    Node* temp = top;
    deletedValue = top->data;
    top = top->next;
    delete temp;

    cout << "Удален элемент: " << deletedValue << endl;
    return top;
}

// 4. Функция печати списка
void printList(Node* top) {
    if (top == nullptr) {
        cout << "Список пустой" << endl;
        return;
    }

    cout << "Содержимое стека (от вершины к основанию): ";
    Node* current = top;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// 5. Функция записи списка в файл
bool saveToFile(Node* top, const char* filename) {
    if (top == nullptr) {
        cout << "Невозможно записать: список пустой" << endl;
        return false;
    }

    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл для записи" << endl;
        return false;
    }

    // Сначала подсчитываем количество элементов
    int count = 0;
    Node* current = top;
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    // Записываем количество элементов
    outFile << count << endl;

    // Записываем все элементы (от вершины к основанию)
    current = top;
    while (current != nullptr) {
        outFile << current->data << " ";
        current = current->next;
    }

    outFile.close();
    cout << "Список успешно записан в файл: " << filename << endl;
    return true;
}

// 6. Функция уничтожения списка (освобождение памяти)
Node* destroyList(Node* top) {
    if (top == nullptr) {
        cout << "Список уже пустой" << endl;
        return nullptr;
    }

    
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
        
    }

   
}

// 7. Функция восстановления списка из файла
Node* restoreFromFile(const char* filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл для чтения" << endl;
        return nullptr;
    }

    int fileSize;
    inFile >> fileSize;

    if (fileSize == 0) {
        cout << "Файл пуст" << endl;
        inFile.close();
        return nullptr;
    }

    // Читаем все элементы из файла во временный массив
    int* tempArray = new int[fileSize];
    for (int i = 0; i < fileSize; i++) {
        inFile >> tempArray[i];
    }
    inFile.close();

    // Восстанавливаем стек, добавляя элементы в обратном порядке
    // так как в файле они записаны от вершины к основанию
    Node* top = nullptr;
    for (int i = fileSize - 1; i >= 0; i--) {
        Node* newNode = new Node;
        newNode->data = tempArray[i];
        newNode->next = top;
        top = newNode;
    }

    delete[] tempArray;
    cout << "Список успешно восстановлен из файла: " << filename << endl;
    return top;
}

// Вспомогательная функция для подсчета размера стека
int getSize(Node* top) {
    int count = 0;
    Node* current = top;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Вспомогательная функция для проверки пустоты
bool isEmpty(Node* top) {
    return top == nullptr;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Node* stack = nullptr;  // Указатель на вершину стека
    const char* filename = "stack_data.txt";

   

    // 1. Создание пустого списка
    cout << "1. Создание пустого стека" << endl;
    stack = createList();
    printList(stack);
    cout << endl;

    // 2. Добавление элементов
    cout << "2. Добавление элементов:" << endl;
    stack = push(stack, 10);
    stack = push(stack, 20);
    stack = push(stack, 30);
    stack = push(stack, 40);
    stack = push(stack, 50);
    printList(stack);
    cout << endl;

    // 3. Удаление элементов
    cout << "3. Удаление элементов:" << endl;
    int deletedValue;
    stack = pop(stack, deletedValue);
    stack = pop(stack, deletedValue);
    printList(stack);
    cout << endl;

    // 4. Добавление новых элементов
    cout << "4. Добавление новых элементов:" << endl;
    stack = push(stack, 60);
    stack = push(stack, 70);
    printList(stack);
    cout << endl;

    // 5. Запись в файл
    cout << "5. Запись стека в файл:" << endl;
    saveToFile(stack, filename);
    cout << endl;

    // 6. Уничтожение списка
    cout << "6. Уничтожение списка:" << endl;
    stack = destroyList(stack);
    printList(stack);
    cout << endl;

    // 7. Восстановление из файла
    cout << "7. Восстановление списка из файла:" << endl;
    stack = restoreFromFile(filename);
    printList(stack);
    cout << endl;

    // 8. Финальное уничтожение
    cout << "8. Финальное уничтожение списка:" << endl;
    stack = destroyList(stack);
    printList(stack);

    return 0;
}