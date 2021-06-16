#include "Database.h"

Database::Database() {
	this->doc = new tinyxml2::XMLDocument;
	cur_dep_index = 0;
	cur_emp_index = 0;
}

Database::Database(const Database& db) {
	this->file_name = db.file_name;
	//this->doc = db.doc; // копируется именно указатель, а не значение, т.к. нет конструктора копий для значения
	this->doc = nullptr;
	this->cur_dep_index = db.cur_dep_index;
	this->cur_emp_index = db.cur_emp_index;
	this->departments = db.departments;
}

Database& Database::operator=(const Database& db) {
	this->file_name = db.file_name;
	this->doc = nullptr;
	//this->doc = db.doc; // копируется именно указатель, а не значение, т.к. нет конструктора копий для значения
	this->cur_dep_index = db.cur_dep_index;
	this->cur_emp_index = db.cur_emp_index;
	this->departments = db.departments;
	return *this;
}


Database::~Database() {
	delete this->doc;
	this->doc = nullptr;
}

void Database::add_dep(Department& dep) {
	this->departments.push_back(dep);
}

void Database::add_emp(Employment& emp) {
	this->departments[this->cur_dep_index].add_employment(emp);
}

void Database::select_dep(int id) {
	if (id > (int)(this->departments.size() - 1) || id < 0) {
		throw std::exception(u8"Нет подразделения с таким индексом\n");
	}
	this->cur_dep_index = id;
}

void Database::select_emp(int id) {
	if (this->departments.size() < 1) {
		throw std::exception(u8"Нет подразделений, в которых можно было бы выбрать работника\n");
	}
	if (id > (int)(this->departments[this->cur_dep_index].get_employments().size() - 1) || id < 0) {
		throw std::exception(u8"В текущем подразделении нет рабочего с таким индексом\n");
	}
	this->cur_emp_index = id;
}

void Database::remove_cur_dep() {
	if (this->departments.size() > 0) {
		this->departments.erase(this->departments.begin() + this->cur_dep_index);
		this->cur_dep_index = 0;
	}
}

void Database::remove_cur_emp() {
	if (this->departments[cur_dep_index].get_employments().size() > 0) {
		this->departments[cur_dep_index].remove_employment(cur_emp_index);
		this->cur_emp_index = 0;
	}
}

void Database::edit_cur_dep(Department& dep) {
	this->departments[this->cur_dep_index] = Department(dep.get_name(), this->departments[this->cur_dep_index].get_number_of_employees(), 
		this->departments[this->cur_dep_index].get_average_salary(), this->departments[this->cur_dep_index].get_employments());
}

void Database::edit_cur_emp(Employment& emp) {
	this->departments[this->cur_dep_index].remplace_employment(this->cur_emp_index, emp);
}

std::string Database::get_formated_data() {
	const std::string TAB = u8"	";
	std::string ans = (this->departments.empty()) ? u8"Нет подразделений\n" : u8"" ;
	int index = 0;
	for (auto i : this->departments) {
		ans += u8"- ";
		if (index == this->cur_dep_index) {
			ans += u8"(*) ";
		}
		ans += std::to_string(index) + u8") " + i.get_name() + u8": количество сотрудников - " + std::to_string(i.get_number_of_employees())
			+ u8", средняя зарплата - " + std::to_string(int(i.get_average_salary())) + u8".\n Сотрудники: \n";
		
		if (i.get_employments().size() <= 0) {
			ans += TAB + u8"- Нет сотрудников\n";
		}
		else {
			int index2 = 0;
			for (auto j : i.get_employments()) {
				ans += TAB + u8"- ";
				if (index == this->cur_dep_index && index2 == this->cur_emp_index) {
					ans += u8"(*) ";
				}
				ans += std::to_string(index2) + u8") "+ j.get_full_name() + ": " + j.get_function() + u8" с зарплатой " + std::to_string(int(j.get_salary())) + u8"\n";

				++index2;
			}
		}
		++index;
		ans += u8"\n";
	}
	return ans;
}

Error_type Database::load_data(std::string input_file_name) {
	this->file_name = input_file_name;

	tinyxml2::XMLError eResult = doc->LoadFile(input_file_name.c_str());
	if (eResult != tinyxml2::XML_SUCCESS) {
		return Error_type::cant_open_file;
	}

	tinyxml2::XMLNode* root = doc->FirstChildElement();
	if (root == nullptr) {
		return Error_type::no_root_element;
	}
	else {
		tinyxml2::XMLElement* dep_xml = root->FirstChildElement();

		while (dep_xml != nullptr) {
			Department dep(dep_xml->Attribute("name"));

			// считывание сотрудников
			tinyxml2::XMLElement* employments_xml = dep_xml->FirstChildElement();

			tinyxml2::XMLElement* employment_xml = employments_xml->FirstChildElement();

			while (employment_xml != nullptr) {
				tinyxml2::XMLElement* surname_xml = employment_xml->FirstChildElement();
				tinyxml2::XMLElement* name_xml = surname_xml->NextSiblingElement();
				tinyxml2::XMLElement* middleName_xml = name_xml->NextSiblingElement();
				tinyxml2::XMLElement* function_xml = middleName_xml->NextSiblingElement();
				tinyxml2::XMLElement* salary_xml = function_xml->NextSiblingElement();

				Employment emp(std::string(surname_xml->GetText()), std::string(name_xml->GetText()), std::string(middleName_xml->GetText()), 
					std::string(function_xml->GetText()), std::stoi(std::string(salary_xml->GetText())));
				dep.add_employment(emp);

				employment_xml = employment_xml->NextSiblingElement();
			}
			this->departments.push_back(dep);
			dep_xml = dep_xml->NextSiblingElement();
		}
	}

	return Error_type::success;
}

Error_type Database::save_data(std::string output_file_name) {
	if (output_file_name == "") {
		output_file_name = this->file_name;
	}

	// TODO

	return Error_type::success;
}
