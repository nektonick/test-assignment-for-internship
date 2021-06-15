#pragma once

#include <vector>

#include "Department.h"
#include "CommandHistory.h"
#include "Commands.h"
#include "Database.h"
#include "Input_output.h"
#include "CommandHistory.h"

class Application {
protected:
	CommandHistory history;
	Database data;
	std::vector<Command*> all_commands;

	// Очищает динамически выделенные команды из all_commands
	void clear_all_commands();

	// Выполнение команды и добавление её в историю (если нужно)
	void executeCommand(Command* command);

	// Сравнивание ввода с шорткатами команд
	Command* parse_user_input(std::string& input);
public:
	Application();

	virtual ~Application();

	std::vector<Command*> generate_available_commands_list();

	// Загрузка датасета
	bool initialise(std::string file_name);

	// Получение и выполнение команд пользователя
	void work_with_user();
};
