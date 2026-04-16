#include "Header2.h"
#include "Header3.h"

int main() {
    Vector v(5);
    v.Add(new Triad(1, 2, 3));
    v.Add(new Time(10, 15, 30));
    v.Add(new Time(23, 59, 59));
    v.Add(new Triad(5, 6, 7));

    cout << "Vector contents:\n";
    v.ShowAll();

    // Утечка памяти допустима в учебных целях, но в реальности надо delete
    return 0;
}