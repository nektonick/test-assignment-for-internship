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

	void clear_all_commands();

	void clear_history();
public:
	Application();

	virtual ~Application();

	void executeCommand(Command* command);

	bool initialise(std::string file_name);

	Command* parse_user_input(std::string& input);

	void work_with_user();
};
