#include "CommandHistory.h"

void CommandHistory::push(Command* command) {
	this->commands.emplace_back(command);
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
