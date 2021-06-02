#pragma once

#include <iostream>


class Input_output
{
public:
	// Принимает u8 строку, выводит её пользователю
	static void print(std::string msg);

	// Получает у пользователя строку
	static std::string read();
};


