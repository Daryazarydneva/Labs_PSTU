#include <iostream>
#include "Set.h"
using namespace std;

int main() {
    cout << "========== TEST 1: Constructor with size 35 ==========\n";
    try {
        Set s1(35);
        cout << "Created successfully" << endl;
    }
    catch (SetException& e) {
        e.print();
    }
    cout << endl;

    cout << "========== TEST 2: Normal work ==========\n";
    Set mySet(5);
    cout << "Initial set: ";
    mySet.print();

    mySet.add(10);
    mySet.add(20);
    mySet.add(30);
    mySet.add(40);
    cout << "After add: ";
    mySet.print();

    mySet[0] = 100;
    mySet[1] = 200;
    cout << "After modify: ";
    mySet.print();
    cout << endl;

    cout << "========== TEST 3: Operator [] exceptions ==========\n";
    cout << "Access index -1: ";
    try {
        int val = mySet[-1];
        cout << "Value: " << val << endl;
    }
    catch (SetException& e) {
        e.print();
    }

    cout << "Access index 100: ";
    try {
        int val = mySet[100];
        cout << "Value: " << val << endl;
    }
    catch (SetException& e) {
        e.print();
    }
    cout << endl;

    cout << "========== TEST 4: Operator != ==========\n";
    Set setA(3);
    setA[0] = 1; setA[1] = 2; setA[2] = 3;

    Set setB(3);
    setB[0] = 1; setB[1] = 2; setB[2] = 3;

    Set setC(3);
    setC[0] = 1; setC[1] = 2; setC[2] = 4;

    cout << "setA = "; setA.print();
    cout << "setB = "; setB.print();
    cout << "setC = "; setC.print();
    cout << "setA != setB: " << (setA != setB ? "true" : "false") << endl;
    cout << "setA != setC: " << (setA != setC ? "true" : "false") << endl;
    cout << endl;

    cout << "========== TEST 5: Operator < (membership) ==========\n";
    Set setD(4);
    setD[0] = 5; setD[1] = 10; setD[2] = 15; setD[3] = 20;
    cout << "Set: "; setD.print();
    cout << "10 < set: " << (10 < setD ? "true (belongs)" : "false") << endl;
    cout << "99 < set: " << (99 < setD ? "true (belongs)" : "false") << endl;
    cout << endl;

    cout << "========== TEST 6: Operator +n iterator ==========\n";
    Set setE(5);
    for (int i = 0; i < 5; i++) setE[i] = i * 10;
    cout << "Set: "; setE.print();

    auto it = setE + 2;
    cout << "Element at index 2 (+2): " << *it << endl;

    cout << "Try step +100: ";
    try {
        auto it2 = setE + 100;
        cout << "Success" << endl;
    }
    catch (SetException& e) {
        e.print();
    }
    cout << endl;

    cout << "========== TEST 7: Delete from empty set ==========\n";
    Set emptySet;
    cout << "Empty set: "; emptySet.print();
    cout << "Try to delete: ";
    try {
        emptySet.remove(0);
        cout << "Success" << endl;
    }
    catch (SetException& e) {
        e.print();
    }
    cout << endl;

    cout << "========== All tests completed ==========\n";

    return 0;
}