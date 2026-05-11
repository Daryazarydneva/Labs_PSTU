#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

template <class T>
struct Node {
    T data;
    Node* left;
    Node* right;
    Node* parent;

    Node(T value) {
        data = value;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

template <class T>
class BinaryTree {
private:
    Node<T>* root;
    Node<T>* buildBalanced(int n) {
        if (n == 0) return nullptr;

        T data;
        cout << "Введите значение узла: ";
        cin >> data;

        Node<T>* newNode = new Node<T>(data);
        int leftCount = n / 2;
        int rightCount = n - leftCount - 1;

        newNode->left = buildBalanced(leftCount);
        if (newNode->left != nullptr) 
            newNode->left->parent = newNode;//B->parent = A

        newNode->right = buildBalanced(rightCount);
        if (newNode->right != nullptr) 
            newNode->right->parent = newNode;

        return newNode;
    }

    // Рекурсивный поиск максимума 
    T findMaxRecursive(Node<T>* node, T& currentMax) {
        if (node == nullptr) return currentMax;

        if (node->data > currentMax) {
            currentMax = node->data;
        }

        // Рекурсивно обходим левое и правое поддеревья
        findMaxRecursive(node->left, currentMax);
        findMaxRecursive(node->right, currentMax);

        return currentMax;
    }


    void convertToSearchTree(Node<T>* node, T* arr, int& index) {
        if (node == nullptr) return;
        // Симметричный обход (слева-направо)
        convertToSearchTree(node->left, arr, index);
        node->data = arr[index++];
        convertToSearchTree(node->right, arr, index);
    }

    // Вспомогательная функция для подсчета количества узлов (для массива)
    int getSize(Node<T>* node) {
        if (node == nullptr) return 0;
        return 1 + getSize(node->left) + getSize(node->right);
    }

    // Рекурсивная печать дерева (горизонтальная, развернутая на 90 градусов)
    void printTree(Node<T>* node, int level) {
        if (node == nullptr) return;
        // Сначала печатаем правое поддерево (оно будет сверху)
        printTree(node->right, level + 1);
        // Отступы
        for (int i = 0; i < level; i++) {
            cout << "    ";
        }
        // Печать значения узла
        cout << node->data << endl;
        // Затем печатаем левое поддерево
        printTree(node->left, level + 1);
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    // Создание идеально сбалансированного дерева (интерфейс)
    void createBalancedTree(int n) {
        root = buildBalanced(n);
    }

    // Поиск максимального элемента (метод обертка)
    T findMax() {
        if (root == nullptr) {
            cerr << "Дерево пусто!" << endl;
            return -1; // или выбросить исключение
        }
        T maxVal = root->data; // Инициализируем корнем
        return findMaxRecursive(root, maxVal);
    }


    void transformToSearchTree() {
        int size = getSize(root);
        if (size == 0) return;

        // 1. Временный массив для хранения данных
        T* arr = new T[size];
        int index = 0;

        // 2. Собрать данные в массив 
        
        copyDataToArray(root, arr, index);

        // 3. Сортируем массив (пузырьком)
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    T temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }

        // 4. Сбросить индекс
        index = 0;
        // 5. Записать отсортированные данные обратно в дерево симметричным обходом
        inOrderAssign(root, arr, index);

        delete[] arr;
    }

    // Вспомогательная копия данных в массив
    void copyDataToArray(Node<T>* node, T* arr, int& index) {
        if (node == nullptr) return;
        copyDataToArray(node->left, arr, index);
        arr[index++] = node->data;
        copyDataToArray(node->right, arr, index);
    }

    // Присвоение данных из массива в узлы (симметричный обход)
    void inOrderAssign(Node<T>* node, T* arr, int& index) {
        if (node == nullptr) return;
        inOrderAssign(node->left, arr, index);
        node->data = arr[index++];
        inOrderAssign(node->right, arr, index);
    }

    // Печать дерева на экран (горизонтальная)
    void print() {
        if (root == nullptr) {
            cout << "Дерево пусто." << endl;
        }
        else {
            cout << "\nСтруктура дерева (повернуто на 90° влево, корень слева):" << endl;
            printTree(root, 0);
        }
    }

    // Деструктор для очистки памяти
    ~BinaryTree() {
        clearTree(root);
    }

    void clearTree(Node<T>* node) {
        if (node == nullptr) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    BinaryTree<double> tree;
    int n;

    // 1. Запрашиваем количество узлов
    cout << "\nВведите количество узлов в идеально сбалансированном дереве: ";
    cin >> n;

    if (n <= 0) {
        cout << "Некорректное количество узлов." << endl;
        return 1;
    }

    // 2. Создаем идеально сбалансированное дерево
    cout << "\nВведите значения узлов (тип double):" << endl;
    tree.createBalancedTree(n);

    // 3. Печатаем дерево
    tree.print();

    // 4. Находим и выводим максимальный элемент
    double maxElem = tree.findMax();
    cout << "\nМаксимальный элемент в дереве: " << maxElem << endl;

    // 5. Преобразуем идеально сбалансированное дерево в дерево поиска
    cout << "\nПреобразование дерева в дерево поиска..." << endl;
    tree.transformToSearchTree();

    // 6. Печатаем новое дерево
    cout << "Дерево поиска (In-Order структура):" << endl;
    tree.print();

    return 0;
}