// 3.7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
using namespace std;
int main()
{
    const int n = 6;
    int arr[n] = { 5, 4, 2, 8, 9, 2 };
    int min = arr[0];
    int max = arr[0];
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";

    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        if (max < arr[i]) { max = arr[i]; }
        if (min > arr[i]) { min = arr[i]; }

    }
    cout << max << " " << min;
    return 0;
}

