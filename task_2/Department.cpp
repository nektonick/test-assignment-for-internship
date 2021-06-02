#include "Department.h"

void Department::recalculate_average_salary() {
	this->average_salary = this->total_salary / this->number_of_employees;
}

Department::Department() {
	name = "";
	number_of_employees = 0;
	average_salary = 0;
	employments = std::vector<Employment>();
	total_salary = 0;
}

Department::Department(std::string input_name, uint64_t input_number_of_employees, 
	long double input_average_salary, std::vector<Employment> input_employments) {

	this->name = input_name;
	this->number_of_employees = input_number_of_employees;
	this->average_salary = input_average_salary;
	this->employments = input_employments;
	this->total_salary = average_salary * number_of_employees;
}

Department::Department(const Department& dep) {
	this->name = dep.name;
	this->number_of_employees = dep.number_of_employees;
	this->average_salary = dep.average_salary;
	this->employments = dep.employments;
	this->total_salary = dep.total_salary;
}

Department& Department::operator= (const Department& dep) {
	Department tmp(dep);
	Department::swap(*this, tmp);
	return *this;
}

Department::~Department(){
	// Ресурсы динамически не выделялись
}

void Department::swap(Department& dep1, Department& dep2) noexcept {
	std::swap(dep1.name, dep2.name);
	std::swap(dep1.number_of_employees, dep2.number_of_employees);
	std::swap(dep1.average_salary, dep2.average_salary);
	std::swap(dep1.employments, dep2.employments);
	std::swap(dep1.total_salary, dep2.total_salary);
}

void Department::add_employment(Employment& emp) {
	this->employments.emplace_back(emp);

	this->number_of_employees += 1;
	this->total_salary += emp.get_salary();
	
	// В целях оптимизации, можно было бы считать среднюю зарплату не каждый раз при добавлении нового сотрудника,
	// а непосредственно когда она нужна (в геттерах, операторах вывода и т.д.). Однако в таком случае легко где-нибудь забыть пересчитать её.
	this->recalculate_average_salary(); 
}

void Department::add_employment(std::string& surname, std::string& name, std::string& middleName, std::string& function, long double& salary) {
	Employment temp(surname, name, middleName, function, salary);
	this->add_employment(temp);
}


void Department::remove_employment(size_t index) {
	this->total_salary -= this->employments[index].get_salary();
	this->number_of_employees -= 1;
	this->recalculate_average_salary();

	this->employments.erase(std::next(employments.begin(), index));
}

void Department::remove_employment(std::string& surname, std::string& name, std::string& middleName) {
	for (size_t i = 0; i < this->employments.size(); ++i) {
		if (employments[i].get_full_name() == (surname + " " + name + " " + middleName)) {
			this->remove_employment(i);
			break;
		}
	}
}

void Department::remplace_employment(size_t index, Employment& new_emp) {
	this->total_salary -= this->employments[index].get_salary();
	this->total_salary += new_emp.get_salary();
	this->recalculate_average_salary();

	this->employments[index] = new_emp;
}

std::string Department::get_name() {
	return this->name;
}

uint64_t Department::get_number_of_employees() {
	return this->number_of_employees;
}

long double Department::get_average_salary() {
	return this->average_salary;
}
