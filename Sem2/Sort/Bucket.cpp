#include <iostream>
using namespace std;

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Простая сортировка вставками для блоков
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Сортировка по блокам
void bucketSort(int arr[], int n, int maxVal) {
    // Количество блоков
    int numBuckets = 5;  // Можно менять

    cout << "Раскладываем элементы по " << numBuckets << " корзинам" << endl;

    // Создаем динамический массив блоков
    // Каждый блок - это массив с указателем на данные
    int** buckets = new int* [numBuckets];
    int* bucketSizes = new int[numBuckets];  // Текущий размер каждого блока
    int* bucketCapacities = new int[numBuckets];  // Вместимость каждого блока

    // Инициализация блоков
    for (int i = 0; i < numBuckets; i++) {
        bucketCapacities[i] = n;  // Максимально может быть n элементов
        buckets[i] = new int[bucketCapacities[i]];
        bucketSizes[i] = 0;
    }

    // Распределяем элементы по блокам
    for (int i = 0; i < n; i++) {
        // Определяем номер блока для текущего элемента
        // Формула: (элемент * количество_блоков) / (максимальное_значение + 1)
        int bucketIndex = (arr[i] * numBuckets) / (maxVal + 1);

        // Гарантируем, что индекс в пределах
        if (bucketIndex >= numBuckets) {
            bucketIndex = numBuckets - 1;
        }

        // Добавляем элемент в блок
        buckets[bucketIndex][bucketSizes[bucketIndex]] = arr[i];
        bucketSizes[bucketIndex]++;

        cout << "  Элемент " << arr[i] << " -> корзина " << bucketIndex << endl;
    }

    // Выводим содержимое блоков
    for (int i = 0; i < numBuckets; i++) {
        cout << "Корзина " << i << ": ";
        for (int j = 0; j < bucketSizes[i]; j++) {
            cout << buckets[i][j] << " ";
        }
        cout << endl;
    }

    // Сортируем каждый блок (используем простую вставками)
    cout << "\nСортируем каждую корзину:" << endl;
    for (int i = 0; i < numBuckets; i++) {
        if (bucketSizes[i] > 0) {
            cout << "  Сортируем корзину " << i << ": ";
            for (int j = 0; j < bucketSizes[i]; j++) {
                cout << buckets[i][j] << " ";
            }
            cout << endl;
            insertionSort(buckets[i], bucketSizes[i]);
            cout << "    Результат: ";
            for (int j = 0; j < bucketSizes[i]; j++) {
                cout << buckets[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Собираем элементы обратно в исходный массив
    cout << "\nСобираем элементы из корзин:" << endl;
    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[index] = buckets[i][j];
            cout << "  " << arr[index] << " ";
            index++;
        }
    }
    cout << endl;

    // Освобождаем память
    for (int i = 0; i < numBuckets; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucketSizes;
    delete[] bucketCapacities;
}

int main() {
    setlocale(LC_ALL, "Ru");
    int arr[] = { 42, 18, 7, 91, 23, 56, 34, 79, 11, 63 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxVal = 100;  // Числа от 0 до 99

    cout << "Исходный массив: ";
    printArray(arr, n);
    cout << endl;

    bucketSort(arr, n, maxVal);

    cout << "\nОтсортированный массив: ";
    printArray(arr, n);

    return 0;
}