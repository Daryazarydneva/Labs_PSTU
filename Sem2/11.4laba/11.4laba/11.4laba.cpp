#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

// Структура узла очереди
struct Node {
    int data;        // Данные узла
    Node* next;      // Указатель на следующий элемент
};

// Структура для хранения указателей на начало и конец очереди
struct Queue {
    Node* front;     // Указатель на начало очереди (первый элемент)
    Node* rear;      // Указатель на конец очереди (последний элемент)
};

// 1. Функция создания пустой очереди
Queue* createQueue() {
    Queue* q = new Queue;
    q->front = nullptr;
    q->rear = nullptr;
    cout << "Создана пустая очередь" << endl;
    return q;
}

// 2. Функция добавления элемента в очередь (в конец)
void enqueue(Queue* q, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (q->rear == nullptr) {
        // Если очередь пуста, новый элемент становится и началом, и концом
        q->front = newNode;
        q->rear = newNode;
    }
    else {
        // Добавляем элемент в конец
        q->rear->next = newNode;
        q->rear = newNode;
    }

    cout << "Добавлен элемент в конец очереди: " << value << endl;
}

// 3. Функция удаления элемента из очереди (из начала)
int dequeue(Queue* q) {
    if (q->front == nullptr) {
        cout << "Ошибка: очередь пуста!" << endl;
        return -1;
    }

    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;

    // Если после удаления очередь стала пустой, обнуляем rear
    if (q->front == nullptr) {
        q->rear = nullptr;
    }

    delete temp;
    cout << "Удален элемент из начала очереди: " << value << endl;
    return value;
}

// 4. Функция печати очереди
void printQueue(Queue* q) {
    if (q->front == nullptr) {
        cout << "Очередь пустая" << endl;
        return;
    }

    cout << "Содержимое очереди (от начала к концу): ";
    Node* current = q->front;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// 5. Функция записи очереди в файл
bool saveQueueToFile(Queue* q, const char* filename) {
    if (q->front == nullptr) {
        cout << "Невозможно записать: очередь пустая" << endl;
        return false;
    }

    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл для записи" << endl;
        return false;
    }

    // Сначала подсчитываем количество элементов
    int count = 0;
    Node* current = q->front;
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    // Записываем количество элементов
    outFile << count << endl;

    // Записываем все элементы (от начала к концу)
    current = q->front;
    while (current != nullptr) {
        outFile << current->data << " ";
        current = current->next;
    }

    outFile.close();
    cout << "Очередь успешно записана в файл: " << filename << endl;
    return true;
}

// 6. Функция уничтожения очереди (освобождение памяти)
void destroyQueue(Queue* q) {
    if (q == nullptr) {
        return;
    }

    if (q->front == nullptr) {
        cout << "Очередь уже пустая" << endl;
        delete q;
        return;
    }

    int count = 0;
    while (q->front != nullptr) {
        Node* temp = q->front;
        q->front = q->front->next;
        delete temp;
        count++;
    }

    q->rear = nullptr;
    delete q;

    cout << "Очередь уничтожена, удалено " << count << " элементов" << endl;
}

// 7. Функция восстановления очереди из файла
Queue* restoreQueueFromFile(const char* filename) {
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
        return createQueue();
    }

    // Создаем новую очередь
    Queue* q = createQueue();

    // Читаем и добавляем элементы в очередь
    for (int i = 0; i < fileSize; i++) {
        int value;
        inFile >> value;
        enqueue(q, value);
    }

    inFile.close();
    cout << "Очередь успешно восстановлена из файла: " << filename << endl;
    return q;
}

// Вспомогательная функция для получения размера очереди
int getQueueSize(Queue* q) {
    int count = 0;
    Node* current = q->front;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Вспомогательная функция для проверки пустоты очереди
bool isQueueEmpty(Queue* q) {
    return q->front == nullptr;
}

// Вспомогательная функция для просмотра первого элемента без удаления
int peek(Queue* q) {
    if (q->front == nullptr) {
        cout << "Очередь пуста" << endl;
        return -1;
    }
    return q->front->data;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Queue* queue = nullptr;
    const char* filename = "queue_data.txt";

    

    // 1. Создание очереди
    cout << "1. Создание пустой очереди" << endl;
    queue = createQueue();
    printQueue(queue);
    cout << endl;

    // 2. Добавление элементов в очередь
    cout << "2. Добавление элементов в конец очереди:" << endl;
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 50);
    printQueue(queue);
    cout << "Первый элемент очереди: " << peek(queue) << endl;
    cout << "Размер очереди: " << getQueueSize(queue) << endl;
    cout << endl;

    // 3. Удаление элементов из очереди
    cout << "3. Удаление элементов из начала очереди:" << endl;
    dequeue(queue);
    dequeue(queue);
    printQueue(queue);
    cout << "Первый элемент очереди: " << peek(queue) << endl;
    cout << "Размер очереди: " << getQueueSize(queue) << endl;
    cout << endl;

    // 4. Добавление новых элементов
    cout << "4. Добавление новых элементов в конец очереди:" << endl;
    enqueue(queue, 60);
    enqueue(queue, 70);
    enqueue(queue, 80);
    printQueue(queue);
    cout << "Первый элемент очереди: " << peek(queue) << endl;
    cout << "Размер очереди: " << getQueueSize(queue) << endl;
    cout << endl;

    // 5. Запись очереди в файл
    cout << "5. Запись очереди в файл:" << endl;
    saveQueueToFile(queue, filename);
    cout << endl;

    // 6. Уничтожение очереди
    cout << "6. Уничтожение очереди:" << endl;
    destroyQueue(queue);
    queue = nullptr;
    // Попытка печати уничтоженной очереди
    if (queue == nullptr) {
        cout << "Очередь уничтожена (указатель null)" << endl;
    }
    cout << endl;

    // 7. Восстановление очереди из файла
    cout << "7. Восстановление очереди из файла:" << endl;
    queue = restoreQueueFromFile(filename);
    if (queue != nullptr) {
        printQueue(queue);
        cout << "Первый элемент очереди: " << peek(queue) << endl;
        cout << "Размер очереди: " << getQueueSize(queue) << endl;
    }
    cout << endl;

    // 8. Дополнительные операции для демонстрации
    cout << "8. Дополнительные операции:" << endl;
    cout << "Удаляем еще один элемент: ";
    dequeue(queue);
    printQueue(queue);
    cout << "Добавляем элемент 90: ";
    enqueue(queue, 90);
    printQueue(queue);
    cout << "Размер очереди: " << getQueueSize(queue) << endl;
    cout << endl;

    // 9. Финальное уничтожение очереди
    cout << "9. Финальное уничтожение очереди:" << endl;
    destroyQueue(queue);
    queue = nullptr;

    return 0;
}