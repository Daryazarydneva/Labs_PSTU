#include <iostream>
using namespace std;

void HANOI(int n, int start, int point, int temp) {
	if (n <= 0) return;
	HANOI(n - 1, start, temp, point);
	cout << start << " => " << point << endl;
	HANOI(n - 1, temp, point, start);
}

int main() {
	int n;
	cin >> n;
	HANOI(n, 1, 3, 2);
	return 0;
}