#pragma once

#include <vector>

#include "Commands.h"

class CommandHistory {
protected:
	std::vector<Command*> commands;
public:
	// Добавление комманды в конец
	void push(Command* command);

	// Получение последней команды. Удаляет её из истории
	Command* pop();

};
