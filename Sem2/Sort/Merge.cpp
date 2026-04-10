#include <iostream>
using namespace std;

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Функция слияния двух отсортированных половин
void merge(int arr[], int left, int mid, int right) {
    // Размеры левой и правой половин
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    cout << "  Сливаем: [" << left << "-" << mid << "] и [" << mid + 1 << "-" << right << "]" << endl;

    // Создаем временные массивы (это единственное место, где нужна доп. память)
    int* leftArray = new int[leftSize];
    int* rightArray = new int[rightSize];

    // Копируем данные во временные массивы
    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = arr[left + i];
    }
    for (int j = 0; j < rightSize; j++) {
        rightArray[j] = arr[mid + 1 + j];
    }

    cout << "    Левая часть: ";
    for (int i = 0; i < leftSize; i++) {
        cout << leftArray[i] << " ";
    }
    cout << endl;
    cout << "    Правая часть: ";
    for (int j = 0; j < rightSize; j++) {
        cout << rightArray[j] << " ";
    }
    cout << endl;

    // Индексы для трех массивов
    int i = 0;  // индекс для leftArray
    int j = 0;  // индекс для rightArray
    int k = left;  // индекс для результирующего массива

    // Сливаем, пока не закончится один из массивов
    while (i < leftSize && j < rightSize) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        }
        else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы из левого массива
    while (i < leftSize) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы из правого массива
    while (j < rightSize) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }

    // Освобождаем временную память
    delete[] leftArray;
    delete[] rightArray;

    cout << "    Результат слияния: ";
    for (int i = left; i <= right; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Рекурсивная сортировка слиянием
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // Находим середину

        cout << "Делим массив: [" << left << "-" << right << "], mid = " << mid << endl;

        // Сортируем левую и правую половины
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Сливаем отсортированные половины
        merge(arr, left, mid, right);
    }
}

// Удобная обертка
void mergeSort(int arr[], int n) {
    mergeSort(arr, 0, n - 1);
}

int main() {
    setlocale(LC_ALL, "Ru");
    int arr[] = { 38, 27, 43, 3, 9, 82, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив: ";
    printArray(arr, n);
    cout << endl;

    mergeSort(arr, n);

    cout << "\nОтсортированный массив: ";
    printArray(arr, n);

    return 0;
}