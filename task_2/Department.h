#pragma once

#include <vector>

#include "Employment.h"

class Department {
protected:
	std::string name;
	uint64_t number_of_employees; // ���������� ���������� ������������� ���� �� �����
	long double average_salary;
	std::vector<Employment> employments;

	long double total_salary; // ��� ������� ������� ��������

	void recalculate_average_salary() {
		this->average_salary = this->total_salary / this->number_of_employees;
	}

public:
	Department();

	Department(std::string input_name, uint64_t input_number_of_employees = 0, long double input_average_salary = 0, std::vector<Employment> input_employments = std::vector<Employment>());

	Department(const Department& dep);

	Department& operator= (const Department& dep);

	~Department();

	void swap(Department& dep1, Department& dep2) noexcept;

	// ��������� ��������� � ����� ������ �����������
	void add_employment(Employment& emp);
	void add_employment(std::string& surname, std::string& name, std::string& middleName, std::string& function, long double& salary);

	// ������� i-���� ���������� � ������, ������ � ����
	void remove_employment(size_t index);

	// ������� ��������� � ��������� ���, ���� ����� ����. ���� ���������� ���������, ������� ������ ������� (� ������� ��������)
	void remove_employment(std::string& surname, std::string& name, std::string& middleName);

	// ������� ������. ��������� ������ ��������� �� ����� �������
	void remplace_employment(size_t index, Employment& new_emp);


	/* ������������� �������:: */

	std::string get_name() {
		return this->name;
	}
	uint64_t get_number_of_employees() {
		return this->number_of_employees;
	}
	long double get_average_salary() {
		return this->average_salary;
	}



};

