#include <iostream>
using namespace std;
int linearSearch(int arr[], int n, int x)
{
	setlocale(LC_ALL, "Russian");
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == x) return i; // элемент найден
	}
	return -1; // массив исчерпан, элемент не найден
}
int main()
{
	int arr[] = { 2, 6, 7, 2, 68, 18, 54, 21, 77, 13 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int x = 18;

	int res = linearSearch(arr, n, x);
	if (res == -1) cout << "Элемент " << x << " не найден" << endl;
	else cout << "Элемент " << x << " найден по индексу " << res << endl;

	return 0;
}