#include "Application.h"

void Application::clear_all_commands() {
	for (size_t i = 0; i < this->all_commands.size(); ++i) {
		delete this->all_commands[i];
	}
	this->all_commands.clear();
}

Application::Application() {
	// ������ ������ ���� �������, ������� ���������� ����� ���������
	this->all_commands = this->generate_available_commands_list();

	// ������� � HelpCommand ��� ������, ����� ����� ���� ������� ������� �� ������ ������� (�������)
	HelpCommand* help = dynamic_cast<HelpCommand*>(all_commands[0]);
	if (help != nullptr) {
		help->set_available_commands(this->all_commands);
	}
	else {
		throw(std::exception("�� ������� �������� ������ � ������� �������"));
	}
}

Application::~Application() {
	clear_all_commands();
	this->history.clear();
}

std::vector<Command*> Application::generate_available_commands_list() {
	std::vector<Command*> ans;

	// ������ ����������� ������ ���� ������� Help (�������)
	ans.push_back(new HelpCommand());

	ans.push_back(new AddDepartmentCommand(&data));
	ans.push_back(new AddEmploymentCommand(&data));

	ans.push_back(new SelectOtherDepartmentCommand(&data));
	ans.push_back(new SelectOtherEmploymentCommand(&data));

	ans.push_back(new RemoveDepartmentCommand(&data));
	ans.push_back(new RemoveEmploymentCommand(&data));

	ans.push_back(new EditDepartmentCommand(&data));
	ans.push_back(new EditEmploymentCommand(&data));

	ans.push_back(new UndoCommand(&data, &history));
	ans.push_back(new RedoCommand(&data, &history));

	ans.push_back(new PrintCommand(&data));
	ans.push_back(new SaveCommand(&data));

	ans.push_back(new ExitCommand());

	return ans;
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
		Input_output::print(u8"���������� ������� ����\n");
		return false;
	}

	return true;

}

Command* Application::parse_user_input(std::string& input) {
	for (size_t i = 0; i < this->all_commands.size(); ++i) {
		if (input == this->all_commands[i]->get_shortcut()) {
			return this->all_commands[i]->get_instance();
		}
	}
	return new ErrorCommand;
}

void Application::work_with_user() {
	Command* command = this->all_commands[0]->get_instance();
	while (dynamic_cast<ExitCommand*>(command) == nullptr) {
		this->executeCommand(command);

		Input_output::print(u8"������� �������: ");
		std::string input = Input_output::read();
		command = this->parse_user_input(input);
	}
}
