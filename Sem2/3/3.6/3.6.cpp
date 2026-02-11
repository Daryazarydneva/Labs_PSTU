// 4.6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
int main()
{
    const int n = 5;
    int arr[n] = { 1,2,3,4,5 };
    int k;
    cin >> k;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    k = k % n;
    
    for (int i = 0; i < k; i++)
    {
        int tmp = arr[n - 1];
        for (int i = n - 1; i > 0; i--)
        {
            arr[i] = arr[i - 1];

        }
        arr[0] = tmp;

    }
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}

