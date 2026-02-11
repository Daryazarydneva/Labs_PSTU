// 9 ВАРИВНТ
// 4.1

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int a;
    cin >> a;
    const int size = 10;
    int arr[size];

    if (a <= 0 || a > size) { return 1; }
 //4.2
 
    for (int i = 0; i < a; i++)
    {
        arr[i] = rand()%100;
        cout << arr[i] << " ";
    }
    cout << endl;

//4.3

    int del;
    cout << "удаляем элемент";
    cin >> del;
    int delPos = -1;//вместо флага. Т.к нет -1 индекса

    for (int i = 0; i < a; i++)
    {
        if (arr[i] == del) { delPos = i; break; }
    }
    
    if (delPos != -1) 
    {
        cout << "Удаляем элемент на позиции " << delPos << endl;
        for (int i = delPos; i < a - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        a--;
    }
    

    cout << "массив после удаления" << endl;
    for (int i = 0; i < a; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    //4.4
    int k;
    cout << "кол-во элементов для сдвига:" << endl;
    cin >> k;

    if (a > 0)
    {
        k = k % a;
        if (k < 0) { k = a + k; }


        for (int j = 0; j < k; j++)
        {
            int tmp = arr[a - 1];

            for (int i = a - 1; i > 0; i--) 
            {
                arr[i] = arr[i - 1];
            }
            arr[0] = tmp;
        }
    }
    else
    {
        cout << "массив пуст" << endl;

    }
    //4.5
    cout << " Итоговый массив после сдвига:" << endl;
    for (int i = 0; i < a; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

   
    return 0;
}


