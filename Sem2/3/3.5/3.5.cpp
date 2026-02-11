// 3.5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
int main()
{
    const int n = 5;
    int arr[n] = { 3, 8, 4, 5, 2 };
    int max = arr[0];

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        if (max < arr[i]) { max = arr[i]; }

    }
    cout << max;

    return 0;

}

