#include <iostream>
using namespace std;

// Функция для вывода массива
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Функция для обмена двух элементов
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Разделение по методу Ломуто
int lomutoPartition(int arr[], int low, int high) {
    // Опорный элемент - последний
    int pivot = arr[high];

    // i указывает на границу элементов, меньших pivot
    int i = low - 1;

    cout << "  Разделяем от " << low << " до " << high << ", pivot = " << pivot << endl;

    // Проходим по всем элементам, кроме последнего
    for (int j = low; j < high; j++) {
        // Если текущий элемент меньше или равен pivot
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            cout << "    Меняем arr[" << i << "]=" << arr[i]
                << " и arr[" << j << "]=" << arr[j] << endl;
        }
    }

    // Ставим pivot на правильное место (после всех меньших)
    swap(arr[i + 1], arr[high]);

    cout << "    Результат: ";
    for (int k = low; k <= high; k++) {
        cout << arr[k] << " ";
    }
    cout << ", pivot на позиции " << i + 1 << endl;

    return i + 1;
}

// Рекурсивная сортировка Ломуто
void lomutoSort(int arr[], int low, int high) {
    if (low < high) {
        // Получаем индекс опорного элемента
        int pivotIndex = lomutoPartition(arr, low, high);

        // Рекурсивно сортируем левую и правую части
        lomutoSort(arr, low, pivotIndex - 1);
        lomutoSort(arr, pivotIndex + 1, high);
    }
}


void lomutoSort(int arr[], int n) {
    lomutoSort(arr, 0, n - 1);
}

int main() {
    setlocale(LC_ALL, "ru");
    int arr[] = { 8, 4, 7, 9, 3, 5, 1, 6, 2 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив: ";
    printArray(arr, n);
    cout << endl;

    lomutoSort(arr, n);

    cout << "\nОтсортированный массив: ";
    printArray(arr, n);

    return 0;
}