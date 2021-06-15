#pragma once

#include <vector>

#include "Commands.h"

class Command;

class CommandHistory {
protected:
	std::vector<Command*> commands;

	// id последней применённой команды 
	// Изменяется при push, undo и redo 
	long long int cur_id = -1;

	// Удаляет все команды, после команды с индексом cur_id
	void clear_tail();
public:
	~CommandHistory();

	// Очищает историю
	void clear();

	// Добавление комманды в конец
	void push(Command* command);

	// Получение последней команды. Удаляет её из истории
	Command* pop();

	void undo();

	void redo();

};
