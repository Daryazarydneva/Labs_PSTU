#include <iostream>
using namespace std;

int main() {
    int rows, cols, number;
    setlocale(LC_CTYPE, "rus");
    // Вводим размеры исходного массива
    cout << "Введите количество строк: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> cols;

    //создаем исходный массив 
    int* data = new int[rows * cols];//строка*столбец = сколько ячеек памяти надо
    int** arr = new int* [rows];
    
    for (int i = 0; i < rows; i++) {
        arr[i] = data + i * cols;
    }

    //исходный массив
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            arr[i][j] = i * cols + j + 1;
            cout << arr[i][j];
        }
        cout << endl;
    }
    cout << endl;
    
    cout << "номер столба для вставки: "; cin >> number;
    
    //новый массив для вставки 
    int* newdata = new int[rows * (cols + 1)];

    //массив указателей для нового массива
    int** newarr = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        newarr[i] = newdata + i * (cols + 1);//на один столбец больше
    }

    //копируем новый массив в старый
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols + 1; j++)
        {
            if (j < number)
                newarr[i][j] = arr[i][j];
            else if (j == number)
            {
                cin >> newarr[i][j];

            }
            else
                newarr[i][j] = arr[i][j - 1];//тк мы сдвигаем из-за добавленного столбца, мы берем от старого массива прошлый индекс и подставляем значение в этом индексе в новый массив

        }
    }
    //выводим результат
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols+1; j++)
        {
            cout << newarr[i][j];
        }
        cout << endl;
    }
    delete[] data;
    delete[] arr;
    delete[] newdata;
    delete[] newarr;

    return 0;
}