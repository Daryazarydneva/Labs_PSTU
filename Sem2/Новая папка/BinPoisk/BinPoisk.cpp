#include <iostream>
using namespace std;

// итеративный вариант
int binarySearch(int arr[], int low, int high, int x)
{
	while (low <= high)
	{
		// чтобы избежать потенциального переполнения (low + high)
		// используем формулу low + (high - low) / 2
		int mid = low + (high - low) / 2;

		if (arr[mid] == x) return mid;

		if (arr[mid] < x) low = mid + 1; // ищем справа
		else high = mid - 1; // ищем слева
	}
	return -1;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int arr[] = { 2, 6, 7, 2, 68, 18, 54, 21, 77, 13 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int x = 54;

	int res = binarySearch(arr, 0, n, x);
	if (res == -1) cout << "Элемент " << x << " не найден" << endl;
	else cout << "Элемент " << x << " найден по индексу " << res << endl;

	return 0;
}
