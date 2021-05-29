#pragma once

#include <string>
class Employment {
protected:
	std::string surname;
	std::string name;
	std::string middleName;
	std::string function;
	long double salary; // Предполагаю, что зарплата может быть и отрицательной, например, из-за штрафов

public:
	Employment();
	
	Employment(std::string input_surname, std::string input_name, std::string input_middleName, std::string input_function, long double input_salary);

	Employment(const Employment& emp);

	Employment& operator= (const Employment& emp);

	void swap(Employment& emp1, Employment& emp2) noexcept;
	
	/* Разнообразные геттеры: */

	std::string get_surname();
	std::string get_name();
	std::string get_middleName();
	std::string get_function();
	long double get_salary();
	std::string get_full_name();
};

