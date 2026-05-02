#include "Dialog.h"

int main() {
    setlocale(LC_ALL, "Russian");   // для вывода русских букв
    Dialog dlg;
    dlg.Execute();
    return 0;
}