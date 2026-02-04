<<<<<<< HEAD
﻿#include <iostream>
using namespace std;
int main()
{
    int n, tmp, max;
    cout << "введите длину последовательсности" << endl;
    cin >> n;

    cout << endl;
    cin >> max;
    for (int i = 2; i <= n; i++)
    {
        cout << endl;
        cin >> tmp;
        if (tmp > max) { max = tmp; }

    }
    cout << max << endl;
}
=======
﻿#include <iostream>
using namespace std;
int main()
{
    int n, tmp, max;
    cout << "введите длину последовательсности" << endl;
    cin >> n;

    cout << endl;
    cin >> max;
    for (int i = 2; i <= n; i++)
    {
        cout << endl;
        cin >> tmp;
        if (tmp > max) { max = tmp; }

    }
    cout << max << endl;
}
>>>>>>> ac2ff8e9902a0609db1464e9d85d9d2a3a3d84a0
