#pragma once
#include "List.h"
#include "Event.h"
class Dialog : public List
{
private:
	int EndState;
public:
	Dialog();
	~Dialog();
	virtual void GetEvent(TEvent& event); //команда от пользователя
	virtual int Execute(); //главный цикл
	virtual void HandleEvent(TEvent& event); // обработчик команд диалога
	virtual void ClearEvent(TEvent& event);  // очистить событие
	int Valid();  // проверка выхода
	void EndExec(); // установить флаг выхода
};


