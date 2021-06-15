#include "Input_output.h"

std::string Input_output::read() {
	std::string ans;
	std::getline(std::cin, ans);
	return ans;
}

void Input_output::print(std::string msg) {
	std::cout << msg;
}