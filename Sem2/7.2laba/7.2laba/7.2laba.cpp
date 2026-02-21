#include <iostream>
#include <cstdarg>
using namespace std;

double max(int type, int count, ...)
{
    va_list args;
    va_start(args, count);

    double maximum;
    if (type == 1) {
        maximum = va_arg(args, int);

        for (int i = 1; i < count; i++) {
            int num = va_arg(args, int);
            if (num > maximum) { maximum = num; }
        }
    }
    else {
        maximum = va_arg(args, double);
        for (int i = 1; i < count; i++) {
            int num = va_arg(args, double);
            if (num > maximum) { maximum = num; }
        }

    }
    va_end(args);
    return maximum;


}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "5 элементов. int " << max(1, 6, 67, 4, 2) << endl;
    cout << "10 элементов. double " << max(2, 10,
        3.14, 2.71, 1.618, 0.5, 2.0,
        4.5, 1.1, 3.3, 2.2, 0.9) << endl;
    cout << "12 элементов. int " << max(1, 12,
        100, 45, 67, 23, 89, 12,
        56, 78, 34, 90, 11, 5) << endl;

    return 0;
    
}
