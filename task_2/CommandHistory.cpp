#include "CommandHistory.h"

void CommandHistory::clear_tail() {
	for (int i = this->commands.size() - 1; i > this->cur_id; --i) {
		delete this->commands[i];
		this->commands.pop_back();
	}
}

CommandHistory::~CommandHistory() {
	this->clear();
}

void CommandHistory::clear() {
	Command* cur = this->pop();
	while (cur != nullptr) {
		delete cur;
		cur = this->pop();
	}
}

void CommandHistory::push(Command* command) {
	if ((int)(this->cur_id) < (int)(this->commands.size() - 1)) {
		this->clear_tail();
	}
	this->commands.emplace_back(command);
	this->cur_id += 1;
	
}

Command* CommandHistory::pop() {
	if (this->commands.size() > 0) {
		Command* ans = this->commands.back();
		this->commands.pop_back();
		return ans;
	}
	else {
		return nullptr;
	}
}

void CommandHistory::undo() {
	if (this->cur_id >= 0) {
		this->commands[cur_id]->undo();
		this->cur_id -= 1;
	}
	else {
		Input_output::print(u8"Нет команд для отмены\n");
	}
}

void CommandHistory::redo() {
	if (this->cur_id + 1 < this->commands.size()) {
		this->cur_id += 1;
		this->commands[cur_id]->redo();
	}
	else {
		Input_output::print(u8"Нет команд для повтора\n");
	}
}
