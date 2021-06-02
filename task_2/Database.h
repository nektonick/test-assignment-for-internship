#pragma once

#include <vector>

#include "tinyxml2.h"

#include "Department.h"


enum class Error_type {
	success = 1,
	cant_open_file,
	no_root_element,
};

class Database {
protected:
	std::string file_name;
	tinyxml2::XMLDocument* doc = nullptr;;
public:
	Department* cur_dep;
	Employment* cur_emp;
	std::vector<Department> departments;

	Database();

	Database(const Database& db);
	
	~Database();

	Error_type load_data(std::string input_file_name);

	Error_type save_data(std::string output_file_name = "");

};

