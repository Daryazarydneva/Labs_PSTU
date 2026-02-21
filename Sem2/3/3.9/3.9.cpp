#include <iostream>
using namespace std;
int main()
{
	const int n = 6;
	int arr[n] = { 1, 2, 3, 4, 5, 6 };
	int tmp[n];
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] % 2 == 0)
		{
			tmp[j] = arr[i];
			j++;
		}
	}
	for (int i = 0; i < j; i++)
	{
		cout << tmp[i] << " ";
	}
	cout << endl;
	return 0;
}