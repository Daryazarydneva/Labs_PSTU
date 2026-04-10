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

// Функция разделения массива
// Возвращает индекс опорного элемента после разделения
int partition(int arr[], int low, int high) {
    // Выбираем опорный элемент (pivot) - возьмем последний
    int pivot = arr[high];

    cout << "  Опорный элемент: " << pivot << endl;

    // Индекс для элемента, который будет меньше опорного
    int i = low - 1;

    // Проходим по всем элементам от low до high-1
    for (int j = low; j < high; j++) {
        // Если текущий элемент меньше или равен опорному
        if (arr[j] <= pivot) {
            i++;  // Увеличиваем индекс меньших элементов
            swap(arr[i], arr[j]);  // Меняем местами
        }
    }

    // Ставим опорный элемент на правильное место
    swap(arr[i + 1], arr[high]);

    // Возвращаем позицию опорного элемента
    return i + 1;
}

// Рекурсивная сортировка Хоара
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        cout << "Сортируем подмассив от " << low << " до " << high << ": ";
        for (int i = low; i <= high; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;

        // Разделяем массив и получаем индекс опорного элемента
        int pivotIndex = partition(arr, low, high);

        cout << "  После разделения: ";
        for (int i = low; i <= high; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << "  Опорный элемент на позиции " << pivotIndex << endl << endl;

        // Рекурсивно сортируем левую часть (элементы меньше опорного)
        quickSort(arr, low, pivotIndex - 1);

        // Рекурсивно сортируем правую часть (элементы больше опорного)
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Удобная обертка для вызова
void quickSort(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Тестовый массив
    int arr[] = { 10, 7, 8, 9, 1, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив: ";
    printArray(arr, n);
    cout << endl;

    quickSort(arr, n);

    cout << "\nОтсортированный массив: ";
    printArray(arr, n);

    return 0;
}