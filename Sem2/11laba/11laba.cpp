#include <iostream>
#include <clocale>
#include <string>
using namespace std;

struct Node //узел
{
    string data;
    Node* pointer_to_next_node = nullptr;
};

struct List //список
{
    Node* head_node = nullptr;
};

void pushBack(List& list, const string& data) //список и данные, добавление элемента в конец списка
{
    Node* new_node = new Node;
    new_node->data = data; // присваиваем полю узла дата данные

    if (list.head_node == nullptr)
    {
        list.head_node = new_node;
    }
    else
    {
        Node* current_node = list.head_node;
        while (current_node->pointer_to_next_node != nullptr)
            current_node = current_node->pointer_to_next_node;
        current_node->pointer_to_next_node = new_node;
    }
}

void pushFront(List& list, const string& data) //список и данные, добавление элемента
{
    Node* new_node = new Node;
    new_node->data = data; // присваиваем полю узла дата данные

    new_node->pointer_to_next_node = list.head_node;
    list.head_node = new_node;
}

//удаление первого узла (головы)
void popFront(List& list)
{
    if (list.head_node == nullptr) return;

    Node* node_to_delete = list.head_node;
    list.head_node = list.head_node->pointer_to_next_node;

    delete node_to_delete;

}

//удаление последнего узла
void popBack(List& list)
{
    if (list.head_node == nullptr) return;

    //только 1 элемент
    if (list.head_node->pointer_to_next_node == nullptr)
    {
        delete list.head_node;
        list.head_node = nullptr;
    }

    Node* current = list.head_node;
    while (current->pointer_to_next_node->pointer_to_next_node != nullptr)
    {
        current = current->pointer_to_next_node;
    }
    delete current->pointer_to_next_node;
    current->pointer_to_next_node = nullptr;
}

//функция вывода списка
void printList(const List& list)
{
    Node* current_node = list.head_node;
    while (current_node != nullptr)
    {
        cout << current_node->data << ' ';
        current_node = current_node->pointer_to_next_node;
    }
    cout << endl;
}

//добавление по индексу
void insertIndex(List& list, const string& data, int index)
{
    if (index < 0) return;

    Node* new_node = new Node;
    new_node->data = data;

    if (index == 0)
    {
        new_node->pointer_to_next_node = list.head_node;
        list.head_node = new_node;
        return;
    }

    Node* current_node = list.head_node;
    int current_index = 0;

    while (current_node != nullptr && current_index < index - 1)
    {
        current_node = current_node->pointer_to_next_node;
        current_index++;
    }

    if (current_node == nullptr)
    {
        delete new_node;
        return;
    }

    new_node->pointer_to_next_node = current_node->pointer_to_next_node;
    current_node->pointer_to_next_node = new_node;
}

//добавление k элементов в конец списка
void fillList(List& list, int k)
{
    string temp;
    cout << "Введите элементы: " << endl;
    for (int i = 0; i < k; i++)
    {
        cout << i + 1 << "-й элемент: ";
        cin >> temp;
        insertIndex(list, temp, i);

    }
}


//удаление узла по индексу
void deleteIndex(List& list, int index)
{
    if (list.head_node == nullptr) return;

    if (index < 0) return;

    if (index == 0)
    {
        Node* node_to_delete = list.head_node;
        list.head_node = list.head_node->pointer_to_next_node;
        delete node_to_delete;
    }

    Node* current_node = list.head_node;
    int current_index = 0;

    while (current_node->pointer_to_next_node != nullptr)
    {
        if (current_index == index - 1)
        {
            Node* node_to_delete = current_node->pointer_to_next_node;
            current_node->pointer_to_next_node = node_to_delete->pointer_to_next_node;
            delete node_to_delete;
        }
        current_node = current_node->pointer_to_next_node;
        current_index++;

    }
}

//удаление элемента по ключу
void deleteKey(List& list, const string& key)
{
    if (list.head_node == nullptr) return;

    if (list.head_node->data == key)
    {
        Node* node_to_delete = list.head_node;
        list.head_node = list.head_node->pointer_to_next_node;
        delete node_to_delete;
        return;
    }
    Node * current_node = list.head_node;
    while (current_node->pointer_to_next_node != nullptr)
    {
        if (current_node->pointer_to_next_node->data == key)
        {
            Node* node_to_delete = current_node->pointer_to_next_node;
            current_node->pointer_to_next_node = node_to_delete->pointer_to_next_node;
            delete node_to_delete;
            return;
        }
        current_node = current_node->pointer_to_next_node;
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    system("chcp 1251");
    system("cls");
    List list;

    int n, k, num;
    string deleting, temp, element;
    cout << "Укажите количество элементов списка: ";
    cin >> n;
    fillList(list, n);
    printList(list);
    cout << "Добавьте первый элемент: ";
    cin >> element;
    pushFront(list, element);
    printList(list);
    cout << "Добавьте последний элемент: ";
    cin >> element;
    pushBack(list, element);
    printList(list);
    cout << "Удаление первого и последнего элементов: " << endl;
    popFront(list);
    popBack(list);
    printList(list);
    cout << "Какой элемент вы хотите удалить?" << endl;
    cin >> deleting;
    deleteKey(list, deleting);
    printList(list);
    cout << "Введите количество элементов, которые хотите добавить: ";
    cin >> k;
    cout << "Введите номер элемента, перед которым хотите добавить новые элементы: ";
    cin >> num;
    cout << "Введите элементы: " << endl;
    for (int i = 0; i < k; i++)
    {
        cout << i + num << "-й элемент: ";
        cin >> temp;
        insertIndex(list, temp, num - 1);
    }
    printList(list);


    return 0;
}