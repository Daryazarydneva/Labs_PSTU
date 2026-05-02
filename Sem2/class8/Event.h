#pragma once
//типы событий 
const int evNothing= 0;
const int evMessage = 100;

//коды команд
const int cmMake = 1; //создать группу (m)
const int cmAdd = 2;  // доб элемент(+)
const int cmDel = 3;  //удалить элемент(-)
const int cmShow = 4; //показать всю группу(s) 
const int cmGetName = 5;//вывести название элемента по номеру(z)
const int cmQuit = 101;//выход(q)

//структура события
struct TEvent {
	int what;
	union {
		int command;
		struct {
			int message;
			int a;
		};
	};
};