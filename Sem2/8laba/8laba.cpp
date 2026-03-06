#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct Pacient {
    string fio;
    string adress;
    string carta;
    string polis;
};

void pepe(int pacientCount)
{
    string stroka;

    fstream myfile("test.txt");
    for (int i = 0; i < pacientCount * 5; i++)
    {
        getline(myfile, stroka);
        cout << stroka << endl;
    }
    myfile.close();
}

Pacient* add(int& pacientCount, Pacient* shnele)
{
    fstream myfile("test.txt");
    string f = "";
    string tmp;

    for (int i = 0; i < pacientCount * 5; i++)
    {
        getline(myfile, tmp);
        f += tmp + "\n";
    }

    myfile.clear(); // очищаю файл
    myfile.close(); // закрываю файл

    myfile.open("test.txt"); // открываю файл снова

    string fio, adress, carta, polis;
    Pacient P;
    getline(cin, fio);
    getline(cin, adress);
    getline(cin, carta);
    getline(cin, polis);

    P = { fio,  adress, carta, polis };
    Pacient* P2 = new Pacient[pacientCount + 1];
    for (int i = 0; i < pacientCount; i++)
    {
        P2[i + 1] = shnele[i];
    }
    P2[0] = P;
    pacientCount++;
    delete[] shnele;

    f = fio + "\n" + adress + "\n" + carta + "\n" + polis + "\n\n" + f;


    myfile << f;
    myfile.close();
    return P2;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(LC_ALL, "ru"); 

    int pacientCount = 4;

    Pacient* shnele = new Pacient[pacientCount];
    shnele = add(pacientCount, shnele);
    cout << endl << endl;
    pepe(pacientCount);

    delete[] shnele;
}

