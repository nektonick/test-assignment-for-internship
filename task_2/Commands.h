#pragma once

#include <string>

#include "Database.h"

class Command {
protected:
	Database* db;
	Database backup;
	std::string shortcut = "";
public:
	// Выполнить команду. Возвращает true, если команду надо добавлять в историю
	virtual bool execute() = 0;
	// Сохраняет текущее состояние данных
	void makeBackup();
	virtual std::string get_info() const = 0;

	// Восстанавливает состояние данных до применения команды
	// Вместо этого можно было бы выполнять "обратную" команду, 
	// тогда требовалось бы меньше памяти на хранение, но пришлось бы писать "обратные" команды
	void undo();

	virtual std::string get_shortcut() const;

	virtual Command* get_copy() = 0;

};

class AddDepartmentCommand : public Command {
protected:

public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual AddDepartmentCommand* get_copy() override;
};

class AddEmploymentCommand : public Command{
protected:

public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual AddEmploymentCommand* get_copy() override;
};

class SelectOtherDepartmentCommand : public Command {
protected:

public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual SelectOtherDepartmentCommand* get_copy() override;
};

class SelectOtherEmploymentCommand : public Command {
protected:

public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual SelectOtherEmploymentCommand* get_copy() override;
};

class RemoveDepartmentCommand : public Command {
protected:

public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual RemoveDepartmentCommand* get_copy() override;
};

class RemoveEmploymentCommand : public Command {
protected:

public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual RemoveEmploymentCommand* get_copy() override;
};

class EditDepartmentCommand : public Command {
protected:
	
public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual EditDepartmentCommand* get_copy() override;
};

class EditEmploymentCommand : public Command {
protected:

public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual EditEmploymentCommand* get_copy() override;
};

class UndoCommand : public Command {
protected:

public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual AddDepartmentCommand* get_copy() override;
};

class RedoCommand : public Command {
protected:

public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual RedoCommand* get_copy() override;
};

class ErrorCommand : public Command  {
protected:

public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual ErrorCommand* get_copy() override;
};

class HelpCommand : public Command {
protected:
	std::vector<Command*> all_commands;
public:
	HelpCommand();
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual HelpCommand* get_copy() override;
};

class PrintCommand : public Command {
protected:
	std::vector<Command*> all_commands;
public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual PrintCommand* get_copy() override;
};

class SaveCommand : public Command {
protected:
	std::vector<Command*> all_commands;
public:
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual SaveCommand* get_copy() override;
};

class ExitCommand : public Command {
protected:
	
	
public:
	ExitCommand();
	virtual bool execute() override;
	virtual std::string get_info() const override;
	virtual ExitCommand* get_copy() override;
};

