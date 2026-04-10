#include <iostream>
using namespace std;

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Сортировка подсчетом для неотрицательных чисел
void countingSort(int arr[], int n, int maxVal) {
    cout << "Создаем массив счетчиков размером " << maxVal + 1 << endl;

    // Создаем массив счетчиков и заполняем нулями
    int* count = new int[maxVal + 1];
    for (int i = 0; i <= maxVal; i++) {
        count[i] = 0;
    }

    // Подсчитываем количество каждого элемента
    cout << "\nПодсчет количества каждого числа:" << endl;
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
        cout << "  arr[" << i << "]=" << arr[i]
            << ", count[" << arr[i] << "]=" << count[arr[i]] << endl;
    }

    // Выводим массив счетчиков
    cout << "\nМассив счетчиков: ";
    for (int i = 0; i <= maxVal; i++) {
        cout << count[i] << " ";
    }
    cout << endl;

    // Преобразуем count в массив префиксных сумм
    // Теперь count[i] будет содержать позицию последнего элемента i
    cout << "\nВычисляем префиксные суммы:" << endl;
    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
        cout << "  count[" << i << "] = " << count[i] << endl;
    }

    // Создаем выходной массив
    int* output = new int[n];

    // Строим отсортированный массив (идем справа налево для стабильности)
    cout << "\nЗаполняем выходной массив:" << endl;
    for (int i = n - 1; i >= 0; i--) {
        int value = arr[i];
        int position = count[value] - 1;
        output[position] = value;
        count[value]--;
        cout << "  Ставим " << value << " на позицию " << position << endl;
    }

    // Копируем обратно в исходный массив
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    // Выводим отсортированный массив
    cout << "\nОтсортированный массив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Освобождаем память
    delete[] count;
    delete[] output;
}

// Универсальная сортировка подсчетом (автоматически находит максимум)
void countingSortAuto(int arr[], int n) {
    if (n <= 0) return;

    // Находим максимальное значение
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    cout << "Максимальное значение: " << maxVal << endl;
    countingSort(arr, n, maxVal);
}

int main() {
    setlocale(LC_ALL, "ru");
    int arr[] = { 4, 2, 2, 8, 3, 3, 1, 5, 4, 2 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив: ";
    printArray(arr, n);
    cout << endl;

    countingSortAuto(arr, n);

    cout << "\nОтсортированный массив: ";
    printArray(arr, n);

    return 0;
}