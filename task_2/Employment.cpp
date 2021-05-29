#include "Employment.h"

inline Employment::Employment() {
	this->surname = "";
	this->name = "";
	this->middleName = "";
	this->function = "";
	this->salary = 0;
}

inline Employment::Employment(std::string input_surname, std::string input_name, std::string input_middleName, std::string input_function, long double input_salary) {
	this->surname = input_surname;
	this->name = input_name;
	this->middleName = input_middleName;
	this->function = input_function;
	this->salary = input_salary;
}

inline Employment::Employment(const Employment& emp) {
	this->surname = emp.surname;
	this->name = emp.name;
	this->middleName = emp.middleName;
	this->function = emp.function;
	this->salary = emp.salary;
}

inline Employment& Employment::operator= (const Employment& emp) {
	Employment tmp(emp);
	Employment::swap(*this, tmp);
	return *this;
}

inline void Employment::swap(Employment& emp1, Employment& emp2) noexcept {
	std::swap(emp1.surname, emp2.surname);
	std::swap(emp1.name, emp2.name);
	std::swap(emp1.middleName, emp2.middleName);
	std::swap(emp1.function, emp2.function);
	std::swap(emp1.salary, emp2.salary);
}

inline std::string Employment::get_surname() {
	return this->surname;
}

inline std::string Employment::get_name() {
	return this->name;
}

inline std::string Employment::get_middleName() {
	return this->middleName;
}

inline std::string Employment::get_function() {
	return this->function;
}

inline long double Employment::get_salary() {
	return this->salary;
}

inline std::string Employment::get_full_name() {
	return (this->surname + " " + this->name + " " + this->middleName);
}
