// 3.12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
int main()
{
    {
        const int n = 3;
        int arr[n][n] =
        {
        { 1,2,3 },
        { 4,5,6 },
        { 7,8,9 }
        };
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        for (int i = 0; i < n; i++)
        {
            arr[i][n-i-1] = 0;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        return 0;

    }
}
