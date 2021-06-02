#include "Application.h"

void Application::clear_all_commands() {
	for (size_t i = 0; i < this->all_commands.size(); ++i) {
		delete this->all_commands[i];
	}
	this->all_commands.clear();
}

void Application::clear_history() {
	Command* cur = this->history.pop();
	while (cur != nullptr) {
		delete cur;
		cur = this->history.pop();
	}
}

Application::Application() {
	// Создаём указатели на все виды команд:
	all_commands.push_back(new AddDepartmentCommand);
	all_commands.push_back(new AddEmploymentCommand);

	all_commands.push_back(new SelectOtherDepartmentCommand);
	all_commands.push_back(new SelectOtherEmploymentCommand);

	all_commands.push_back(new RemoveDepartmentCommand);
	all_commands.push_back(new RemoveEmploymentCommand);

	all_commands.push_back(new EditDepartmentCommand);
	all_commands.push_back(new EditEmploymentCommand);

	all_commands.push_back(new UndoCommand);
	all_commands.push_back(new RedoCommand);

	// all_commands.push_back(new ErrorCommand); // Служебная команда
	all_commands.push_back(new HelpCommand);

	all_commands.push_back(new PrintCommand);
	all_commands.push_back(new SaveCommand);

	all_commands.push_back(new ExitCommand);

}

Application::~Application() {
	clear_all_commands();
	clear_history();
}

void Application::executeCommand(Command* command) {
	if (command->execute()) {
		history.push(command);
	}
	else {
		delete command;
	}
}

bool Application::initialise(std::string file_name) {
	if (this->data.load_data(file_name) != Error_type::success) {
		Input_output::print(u8"Невозможно считать файл\n");
		return false;
	}

	return true;

}

Command* Application::parse_user_input(std::string& input) {
	for (size_t i = 0; i < this->all_commands.size(); ++i) {
		if (input == this->all_commands[i]->get_shortcut()) {
			return this->all_commands[i]->get_copy();
		}
	}
	return new ErrorCommand;
}

void Application::work_with_user() {
	Command* command = new HelpCommand();
	while (dynamic_cast<ExitCommand*>(command) == nullptr) {
		this->executeCommand(command);

		Input_output::print(u8"Введите команду: ");
		std::string input = Input_output::read();
		command = this->parse_user_input(input);
	}
}
