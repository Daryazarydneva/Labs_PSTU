#include <iostream>
using namespace std;

// итеративный вариант
int interpolationSearch(int arr[], int low, int high, int x)
{
    // пока границы не пересеклись и искомое значение попадает в текущий диапазон
    while (low <= high && x >= arr[low] && x <= arr[high])
    {
        // защита от деления на ноль, если все оставшиеся элементы равны
        if (low == high || arr[low] == arr[high])
        {
            if (arr[low] == x) return low;
            return -1;
        }

        // Формула интерполяции
        int pos = low + (((x - arr[low]) * (high - low)) / (arr[high] - arr[low]));

        if (arr[pos] == x) return pos;

        if (arr[pos] < x)
            low = pos + 1;  // ищем справа (в больших числах)
        else
            high = pos - 1; // ищем слева (в меньших числах)
    }
    return -1; // элемент не найден
}

int main() {
    setlocale(LC_ALL, "Russian");
    int arr1[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int x1 = 70;

    int result1 = interpolationSearch(arr1, 0, n1 - 1, x1);
    if (result1 != -1) {
        cout << "Элемент " << x1 << " найден на индексе " << result1 << endl;
    }
    else {
        cout << "Элемент " << x1 << " не найден" << endl;
    }
    cout << endl;
}

    