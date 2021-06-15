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

	// ������� ����������� ���������� ������� �� all_commands
	void clear_all_commands();

	// ���������� ������� � ���������� � � ������� (���� �����)
	void executeCommand(Command* command);

	// ����������� ����� � ���������� ������
	Command* parse_user_input(std::string& input);
public:
	Application();

	virtual ~Application();

	std::vector<Command*> generate_available_commands_list();

	// �������� ��������
	bool initialise(std::string file_name);

	// ��������� � ���������� ������ ������������
	void work_with_user();
};
