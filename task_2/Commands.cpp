#include "Commands.h"

Command::Command(std::string input_shortcut) {
	this->db = nullptr;
	this->shortcut = input_shortcut;
}

Command::Command(Database* database, std::string input_shortcut) {
	this->db = database;
	this->shortcut = input_shortcut;
}

void Command::make_backup() {
	this->backup = *this->db;
}

void Command::make_backup_after_exec() {
	this->backup_after_exec = *this->db;
}

void Command::undo() {
	*this->db = this->backup;
}

void Command::redo() {
	*this->db = this->backup_after_exec;
}

std::string Command::get_shortcut() const {
	return this->shortcut;
}

AddDepartmentCommand::AddDepartmentCommand(Database* database, std::string input_shortcut) : Command(database, input_shortcut) {

}

bool AddDepartmentCommand::execute() {
	this->make_backup();
	Input_output::print(u8"Введите название нового подразделения: ");
	std::string dep_name = Input_output::read();
	Department dep(dep_name);
	this->db->add_dep(dep);

	this->make_backup_after_exec();
	return true;
}

std::string AddDepartmentCommand::get_info() const {
	std::string ans = u8"AddDepartmentCommand. Для вызова введите: " + this->shortcut + u8"\nДобавляет подразделение\n";
	return ans;
}

AddDepartmentCommand* AddDepartmentCommand::get_instance() {
	return new AddDepartmentCommand(this->db);
}

AddEmploymentCommand::AddEmploymentCommand(Database* database, std::string input_shortcut) : Command(database, input_shortcut) {

}

bool AddEmploymentCommand::execute() {
	this->make_backup();
	Input_output::print(u8"Введите через пробел ФИО сотрудника: ");
	std::string surname, name, middleName; std::istringstream(Input_output::read()) >> surname >> name >> middleName;
	Input_output::print(u8"Введите должность сотрудника: ");
	std::string function = Input_output::read();
	Input_output::print(u8"Введите зароботную плату сотрудника: ");
	long double salary; std::istringstream (Input_output::read()) >> salary;
	
	Employment emp(surname, name, middleName, function, salary);
	this->db->add_emp(emp);

	this->make_backup_after_exec();
	return true;
}

std::string AddEmploymentCommand::get_info() const {
	std::string ans = u8"AddEmploymentCommand. Для вызова введите: " + this->shortcut + u8"\nДобавляет сотрудника в текущее подразделение\n";
	return ans;
}

AddEmploymentCommand* AddEmploymentCommand::get_instance() {
	return new AddEmploymentCommand(this->db);
}

SelectOtherDepartmentCommand::SelectOtherDepartmentCommand(Database* database, std::string input_shortcut) : Command(database, input_shortcut) {

}

bool SelectOtherDepartmentCommand::execute() {
	this->make_backup();
	Input_output::print(u8"Введите id подразделения: ");
	int id; std::istringstream(Input_output::read()) >>id;
	try	{
		this->db->select_dep(id);
	}
	catch (const std::exception& e) {
		Input_output::print(e.what());
	}
	

	this->make_backup_after_exec();
	return true;
}

std::string SelectOtherDepartmentCommand::get_info() const {
	std::string ans = u8"SelectOtherDepartmentCommand. Для вызова введите: " + this->shortcut + u8"\nПозволяет выбрать подразделение в качестве текущего\n";
	return ans;
}

SelectOtherDepartmentCommand* SelectOtherDepartmentCommand::get_instance() {
	return new SelectOtherDepartmentCommand(this->db);
}

SelectOtherEmploymentCommand::SelectOtherEmploymentCommand(Database* database, std::string input_shortcut) : Command(database, input_shortcut) {

}

bool SelectOtherEmploymentCommand::execute() {
	this->make_backup();
	Input_output::print(u8"Введите id сотрудника: ");
	int id; std::istringstream(Input_output::read()) >> id;

	try {
		this->db->select_emp(id);
	}
	catch (const std::exception& e) {
		Input_output::print(e.what());
	}

	this->make_backup_after_exec();
	return true;
}

std::string SelectOtherEmploymentCommand::get_info() const {
	std::string ans = u8"SelectOtherEmploymentCommand. Для вызова введите: " + this->shortcut + u8"\nПозволяет выбрать текущего сотрудника текущего подразделения\n";
	return ans;
}

SelectOtherEmploymentCommand* SelectOtherEmploymentCommand::get_instance() {
	return new SelectOtherEmploymentCommand(this->db);
}

RemoveDepartmentCommand::RemoveDepartmentCommand(Database* database, std::string input_shortcut) : Command(database, input_shortcut) {

}

bool RemoveDepartmentCommand::execute() {
	this->make_backup();
	this->db->remove_cur_dep();

	this->make_backup_after_exec();
	return true;
}

std::string RemoveDepartmentCommand::get_info() const {
	std::string ans = u8"RemoveDepartmentCommand. Для вызова введите: " + this->shortcut + u8"\nУдаляет текущее подразделение вместе и его сотрудников\n";
	return ans;
}

RemoveDepartmentCommand* RemoveDepartmentCommand::get_instance() {
	return new RemoveDepartmentCommand(this->db);
}

RemoveEmploymentCommand::RemoveEmploymentCommand(Database* database, std::string input_shortcut) : Command(database, input_shortcut) {

}

bool RemoveEmploymentCommand::execute() {
	this->make_backup();
	this->db->remove_cur_emp();

	this->make_backup_after_exec();
	return true;
}

std::string RemoveEmploymentCommand::get_info() const {
	std::string ans = u8"RemoveEmploymentCommand. Для вызова введите: " + this->shortcut + u8"\nУдаляет текущего сотрудника текущего подразделения\n";
	return ans;
}

RemoveEmploymentCommand* RemoveEmploymentCommand::get_instance() {
	return new RemoveEmploymentCommand(this->db);
}

EditDepartmentCommand::EditDepartmentCommand(Database* database, std::string input_shortcut) : Command(database, input_shortcut) {

}

bool EditDepartmentCommand::execute() {
	this->make_backup();
	Input_output::print(u8"Введите новое название подразделения: ");
	std::string dep_name = Input_output::read();
	Department dep(dep_name);
	this->db->edit_cur_dep(dep);

	this->make_backup_after_exec();
	return true;
}

std::string EditDepartmentCommand::get_info() const {
	std::string ans = u8"EditDepartmentCommand. Для вызова введите: " + this->shortcut + u8"\nПозволяет редактировать текущее подразделение\n";
	return ans;
}

EditDepartmentCommand* EditDepartmentCommand::get_instance() {
	return new EditDepartmentCommand(this->db);
}

EditEmploymentCommand::EditEmploymentCommand(Database* database, std::string input_shortcut) : Command(database, input_shortcut) {

}

bool EditEmploymentCommand::execute() {
	this->make_backup();
	Input_output::print(u8"Введите новое ФИО сотрудника (через пробел): ");
	std::string surname, name, middleName; std::istringstream(Input_output::read()) >> surname >> name >> middleName;
	Input_output::print(u8"Введите новую должность сотрудника: ");
	std::string function; std::istringstream(Input_output::read()) >> function;
	Input_output::print(u8"Введите зароботную плату сотрудника: ");
	long double salary; std::istringstream(Input_output::read()) >> salary;

	Employment emp(surname, name, middleName, function, salary);
	this->db->add_emp(emp);

	this->make_backup_after_exec();
	return true;
}

std::string EditEmploymentCommand::get_info() const {
	std::string ans = u8"EditEmploymentCommand. Для вызова введите: " + this->shortcut + u8"\nПозволяет редактировать текущего работника текущего подразделения\n";
	return ans;
}

EditEmploymentCommand* EditEmploymentCommand::get_instance() {
	return new EditEmploymentCommand(this->db);
}

UndoCommand::UndoCommand(Database* database, CommandHistory* history, std::string input_shortcut) : Command(database, input_shortcut) {
	this->history = history;
}

bool UndoCommand::execute() {
	this->history->undo();
	return false;
}

std::string UndoCommand::get_info() const {
	std::string ans = u8"UndoCommand. Для вызова введите: " + this->shortcut + u8"\nОтменяет последнее действие\n";
	return ans;
}

UndoCommand* UndoCommand::get_instance() {
	return new UndoCommand(this->db, this->history);
}

RedoCommand::RedoCommand(Database* database, CommandHistory* history, std::string input_shortcut) : Command(database, input_shortcut) {
	this->history = history;
}

bool RedoCommand::execute() {
	this->history->redo();
	return false;
}

std::string RedoCommand::get_info() const {
	std::string ans = u8"RedoCommand. Для вызова введите: " + this->shortcut + u8"\nВозвращает отменённое действие\n";
	return ans;
}

RedoCommand* RedoCommand::get_instance() {
	return new RedoCommand(this->db, this->history);
}

ErrorCommand::ErrorCommand() : Command("") {

}

bool ErrorCommand::execute() {
	Input_output::print(u8"Ошибка, введена неверная команда. Введите help для просмотра доступных команд.\n");
	return false;
}

std::string ErrorCommand::get_info() const {
	std::string ans = u8"ErrorCommand. Служебная функция. Сообщает пользователю о неверном вводе команды\n";
	return ans;
}

ErrorCommand* ErrorCommand::get_instance() {
	return new ErrorCommand();
}


HelpCommand::HelpCommand(std::string input_shortcut) : Command(input_shortcut) {

}

bool HelpCommand::execute() {
	Input_output::print(u8"Доступные команды:\n");
	std::string ans = u8"";
	for (auto i : this->all_commands) {
		ans += i->get_info() + u8"\n";
	}
	Input_output::print(ans);
	return false;
}

std::string HelpCommand::get_info() const {
	std::string ans = u8"HelpCommand. Для вызова введите: " + this->shortcut + u8"\nВыводит доступные команды с их Для вызова введитеами и описаниями\n";
	return ans;
}

HelpCommand* HelpCommand::get_instance() {
	HelpCommand* ans = new HelpCommand();
	ans->set_available_commands(this->all_commands);
	return ans;
}

PrintCommand::PrintCommand(Database* database, std::string input_shortcut) : Command(database, input_shortcut) {

}

bool PrintCommand::execute() {
	Input_output::print(this->db->get_formated_data());
	return false;
}

std::string PrintCommand::get_info() const {
	std::string ans = u8"PrintCommand. Для вызова введите: " + this->shortcut + u8"\nВыводит информацию обо всез сотрудниках и подразделениях\n";
	return ans;
}

PrintCommand* PrintCommand::get_instance() {
	return new PrintCommand(this->db);
}

SaveCommand::SaveCommand(Database* database, std::string input_shortcut) : Command(database, input_shortcut) {}

bool SaveCommand::execute() {
	Input_output::print(u8"Данная команда не была реализована\n");
	//Input_output::print(u8"Введите название файла для сохранения, или просто нажмите enter для записи в исходный файл: ");
	//this->db->save_data(Input_output::read());
	return false;
}

std::string SaveCommand::get_info() const {
	std::string ans = u8"SaveCommand. Для вызова введите: " + this->shortcut + u8"\nСохраняет изменения\n";
	return ans;
}

SaveCommand* SaveCommand::get_instance() {
	return new SaveCommand(this->db);
}



ExitCommand::ExitCommand(std::string input_shortcut) : Command(input_shortcut) {

}

bool ExitCommand::execute() {

	return false;
}

std::string ExitCommand::get_info() const {
	std::string ans = u8"ExitCommand. Для вызова введите: " + this->shortcut + u8"\nВыход без сохранения изменений\n";
	return ans;
}

ExitCommand* ExitCommand::get_instance() {
	return new ExitCommand();
}
