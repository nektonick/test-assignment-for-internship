#pragma once

#include <vector>

#include "tinyxml2.h"

#include "Department.h"

#include <iostream>


enum class Error_type {
	success = 1,
	cant_open_file,
	no_root_element,
};

class Database {
protected:
	std::string file_name;
	tinyxml2::XMLDocument* doc = nullptr;
public:
	int cur_dep_index = 0;
	int cur_emp_index = 0;
	std::vector<Department> departments;

	Database();

	Database(const Database& db);

	Database& operator=(const Database& db);

	~Database();

	void add_dep(Department& dep);

	void add_emp(Employment& emp);

	void select_dep(int id);

	void select_emp(int id);

	void remove_cur_dep();

	void remove_cur_emp();

	void edit_cur_dep(Department& dep);

	void edit_cur_emp(Employment& emp);

	// Возвращает строку с информацией о сотрудниках и подразделениях
	std::string get_formated_data();

	Error_type load_data(std::string input_file_name);

	Error_type save_data(std::string output_file_name = "");

};

