#pragma once

#include <string>
#include <sstream>

#include "Database.h"
#include "Input_output.h"
#include "CommandHistory.h"

class CommandHistory;

class Command {
protected:
	Database* db;
	std::vector<Department> backup;
	std::vector<Department> backup_after_exec;
	std::string shortcut = "";
public:
	Command(std::string input_shortcut);
	Command(Database* database, std::string input_shortcut = "");
	// Выполнить команду. Возвращает true, если команду надо добавлять в историю
	virtual bool execute() = 0;

	// Сохраняет текущее состояние данных до применения команды
	void make_backup();

	// Сохраняет текущее состояние данных после применения команды
	void make_backup_after_exec();

	virtual std::string get_info() const = 0;

	// Восстанавливает состояние данных до применения команды
	// Вместо этого можно было бы выполнять "обратную" команду.
	// Тогда требовалось бы меньше памяти на хранение, но пришлось бы написать "обратные" команды
	void undo();

	// Восстанавливает данные как после применения команды
	void redo();

	// Получение шортката команд (для консольной реализации это ключевое слово, которое нужно ввести для вызова этой команды)
	virtual std::string get_shortcut() const;

	// Получение динамически созданного объекта команды данного типа.
	virtual Command* get_instance() = 0;

};

class AddDepartmentCommand : public Command {
protected:

public:
	AddDepartmentCommand(Database* database, std::string input_shortcut = "add dep");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual AddDepartmentCommand* get_instance() override;
};

class AddEmploymentCommand : public Command{
protected:

public:
	AddEmploymentCommand(Database* database, std::string input_shortcut = "add emp");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual AddEmploymentCommand* get_instance() override;
};

class SelectOtherDepartmentCommand : public Command {
protected:

public:
	SelectOtherDepartmentCommand(Database* database, std::string input_shortcut = "select dep");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual SelectOtherDepartmentCommand* get_instance() override;
};

class SelectOtherEmploymentCommand : public Command {
protected:

public:
	SelectOtherEmploymentCommand(Database* database, std::string input_shortcut = "select emp");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual SelectOtherEmploymentCommand* get_instance() override;
};

class RemoveDepartmentCommand : public Command {
protected:

public:
	RemoveDepartmentCommand(Database* database, std::string input_shortcut = "remove dep");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual RemoveDepartmentCommand* get_instance() override;
};

class RemoveEmploymentCommand : public Command {
protected:

public:
	RemoveEmploymentCommand(Database* database, std::string input_shortcut = "remove emp");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual RemoveEmploymentCommand* get_instance() override;
};

class EditDepartmentCommand : public Command {
protected:
	
public:
	EditDepartmentCommand(Database* database, std::string input_shortcut = "edit dep");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual EditDepartmentCommand* get_instance() override;
};

class EditEmploymentCommand : public Command {
protected:

public:
	EditEmploymentCommand(Database* database, std::string input_shortcut = "edit emp");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual EditEmploymentCommand* get_instance() override;
};

class UndoCommand : public Command {
protected:
	CommandHistory* history;
public:
	UndoCommand(Database* database, CommandHistory* history, std::string input_shortcut = "undo");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual UndoCommand* get_instance() override;
};

class RedoCommand : public Command {
protected:
	CommandHistory* history;
public:
	RedoCommand(Database* database, CommandHistory* history, std::string input_shortcut = "redo");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual RedoCommand* get_instance() override;
};

class ErrorCommand : public Command  {
protected:

public:
	ErrorCommand();
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual ErrorCommand* get_instance() override;
};

class HelpCommand : public Command {
protected:
	std::vector<Command*> all_commands;
public:
	HelpCommand(std::string input_shortcut = "help");

	void set_available_commands(std::vector<Command*>& commands) {
		this->all_commands = commands;
	}

	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual HelpCommand* get_instance() override;
};

class PrintCommand : public Command {
protected:
	std::vector<Command*> all_commands;
public:
	PrintCommand(Database* database, std::string input_shortcut = "print");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual PrintCommand* get_instance() override;
};

class SaveCommand : public Command {
protected:
	std::vector<Command*> all_commands;
public:
	SaveCommand(Database* database, std::string input_shortcut = "save");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual SaveCommand* get_instance() override;
};

class ExitCommand : public Command {
protected:
	
	
public:
	ExitCommand(std::string input_shortcut = "exit");
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual ExitCommand* get_instance() override;
};

