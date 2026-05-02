#include "Dialog.h"
#include <string>
#include <cstdlib>

Dialog::Dialog() : List(), EndState(0) {}
Dialog::~Dialog() {}

void Dialog::ClearEvent(TEvent& event) {
    event.what = evNothing;
}

void Dialog::EndExec() {
    EndState = 1;
}

int Dialog::Valid() {
    return EndState == 1;
}

void Dialog::GetEvent(TEvent& event) {
    string s;
    cout << "> ";
    cin >> s;
    char code = s[0];
    // допустимые команды: m, +, -, s, z, q
    if (string("m+-szq").find(code) != string::npos) {
        event.what = evMessage;
        switch (code) {
        case 'm': event.command = cmMake; break;
        case '+': event.command = cmAdd;  break;
        case '-': event.command = cmDel;  break;
        case 's': event.command = cmShow; break;
        case 'z': event.command = cmGetName; break;
        case 'q': event.command = cmQuit; break;
        }
        // парамерт команды (если есть)
        if (s.length() > 1) {
            string param = s.substr(1);
            event.a = atoi(param.c_str());
        }
        else {
            event.a = 0;
        }
    }
    else {
        event.what = evNothing;
    }
}

void Dialog::HandleEvent(TEvent& event) {
    if (event.what == evMessage) {
        switch (event.command) {
        case cmMake:
            // создать группу заданного размера
            size = event.a;
            if (beg) delete[] beg;
            beg = new Object * [size];
            cur = 0;
            ClearEvent(event);
            cout << "Создана группа на " << size << " элементов." << endl;
            break;
        case cmAdd:
            Add();
            ClearEvent(event);
            break;
        case cmDel:
            Del();
            ClearEvent(event);
            break;
        case cmShow:
            Show();
            ClearEvent(event);
            break;
        case cmGetName: {
            int idx = event.a - 1; // пользователь вводит номер с 1
            if (idx >= 0 && idx < cur && beg[idx] != nullptr) {
                // отправить событие cmGetName конкретному объекту
                TEvent e2;
                e2.what = evMessage;
                e2.command = cmGetName;
                beg[idx]->HandleEvent(e2);
            }
            else {
                cout << "Неверный номер элемента." << endl;
            }
            ClearEvent(event);
            break;
        }
        case cmQuit:
            EndExec();
            ClearEvent(event);
            break;
        default:
            // неизвестная команда – передаём группе
            List::HandleEvent(event);
            ClearEvent(event);
            break;
        }
    }
}

int Dialog::Execute() {
    TEvent event;
    do {
        EndState = 0;
        GetEvent(event);
        if (event.what != evNothing)
            HandleEvent(event);
    } while (!Valid());
    return EndState;
}