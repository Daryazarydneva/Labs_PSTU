// 5Laba.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_CTYPE, "rus");
    int n;//кол-во матриц
    int size;//размер матриц
    const int max_s = 100;//максимальный размер матриц
    cout << "введите кол-во матриц";
    cin >> n;
    cout << "введите размер матриц";
    cin >> size;

    if (size > max_s) { return 1; }

    int max_sum = -1000;//максимальное значение суммы(может быть отрицательным)

    for (int index = 0; index < n; index++)
    {
        int matr[max_s][max_s];

        cout << "введите элементы матрицы";
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cin >> matr[i][j];

            }
        }
        int sum = 0;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < i; j++)
            {
                sum += matr[i][j];
            }
        }
        cout << "сумма элементов ниже главной диагонали: " << sum << endl;

        if (sum > max_sum) { max_sum = sum; }
    }
    cout << "максимальное значение суммы главной диагонали: " << max_sum<<endl;
    return 0;
}

