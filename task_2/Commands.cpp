#include "Commands.h"

void Command::makeBackup() {
	backup = *db;
}

void Command::undo() {
	*db = backup;
}

std::string Command::get_shortcut() const {
	return this->shortcut;
}

bool AddDepartmentCommand::execute() {


	return true;
}

std::string AddDepartmentCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n��������� �������������\n";
	return ans;
}

AddDepartmentCommand* AddDepartmentCommand::get_copy() {
	return new AddDepartmentCommand;
}

bool AddEmploymentCommand::execute() {

	return true;
}

std::string AddEmploymentCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n��������� ���������� � ������� �������������\n";
	return ans;
}

AddEmploymentCommand* AddEmploymentCommand::get_copy() {
	return new AddEmploymentCommand;
}

bool SelectOtherDepartmentCommand::execute() {

	return true;
}

std::string SelectOtherDepartmentCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n��������� ������� ������������� � �������� ��������\n";
	return ans;
}

SelectOtherDepartmentCommand* SelectOtherDepartmentCommand::get_copy() {
	return new SelectOtherDepartmentCommand;
}

bool SelectOtherEmploymentCommand::execute() {

	return true;
}

std::string SelectOtherEmploymentCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n��������� ������� �������� ���������� �������� �������������\n";
	return ans;
}

SelectOtherEmploymentCommand* SelectOtherEmploymentCommand::get_copy() {
	return new SelectOtherEmploymentCommand;
}

bool RemoveDepartmentCommand::execute() {

	return true;
}

std::string RemoveDepartmentCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n������� ������� ������������� ������ � ��� �����������\n";
	return ans;
}

RemoveDepartmentCommand* RemoveDepartmentCommand::get_copy() {
	return new RemoveDepartmentCommand;
}

bool RemoveEmploymentCommand::execute() {

	return true;
}

std::string RemoveEmploymentCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n������� �������� ���������� �������� �������������\n";
	return ans;
}

RemoveEmploymentCommand* RemoveEmploymentCommand::get_copy() {
	return new RemoveEmploymentCommand;
}

bool EditDepartmentCommand::execute() {

	return true;
}

std::string EditDepartmentCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n��������� ������������� ������� �������������\n";
	return ans;
}

EditDepartmentCommand* EditDepartmentCommand::get_copy() {
	return new EditDepartmentCommand;
}

bool EditEmploymentCommand::execute() {

	return true;
}

std::string EditEmploymentCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n��������� ������������� �������� ��������� �������� �������������\n";
	return ans;
}

EditEmploymentCommand* EditEmploymentCommand::get_copy() {
	return new EditEmploymentCommand;
}

bool UndoCommand::execute() {

	return false;
}

std::string UndoCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n�������� ��������� ��������\n";
	return ans;
}

AddDepartmentCommand* UndoCommand::get_copy() {
	return new AddDepartmentCommand;
}

bool RedoCommand::execute() {

	return false;
}

std::string RedoCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n���������� ��������� ��������\n";
	return ans;
}

RedoCommand* RedoCommand::get_copy() {
	return new RedoCommand;
}

bool ErrorCommand::execute() {

	return false;
}

std::string ErrorCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n��������� �������. �������� ������������ � �������� �������\n";
	return ans;
}

ErrorCommand* ErrorCommand::get_copy() {
	return new ErrorCommand;
}

HelpCommand::HelpCommand() {
	this->shortcut = "help";
}

bool HelpCommand::execute() {

	return false;
}

std::string HelpCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n������� ��������� ������� � �� ���������� � ����������\n";
	return ans;
}

HelpCommand* HelpCommand::get_copy() {
	return new HelpCommand;
}

bool PrintCommand::execute() {

	return false;
}

std::string PrintCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n������� ���������� ��� ���� ����������� � ��������������\n";
	return ans;
}

PrintCommand* PrintCommand::get_copy() {
	return new PrintCommand;
}

bool SaveCommand::execute() {

	return false;
}

std::string SaveCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n��������� ���������\n";
	return ans;
}

SaveCommand* SaveCommand::get_copy() {
	return new SaveCommand;
}

ExitCommand::ExitCommand() {
	this->shortcut = "exit";
}

bool ExitCommand::execute() {

	return false;
}

std::string ExitCommand::get_info() const {
	std::string ans = u8"�������: " + this->shortcut + u8"\n����� ��� ���������� ���������\n";
	return ans;
}

ExitCommand* ExitCommand::get_copy() {
	return new ExitCommand;
}
