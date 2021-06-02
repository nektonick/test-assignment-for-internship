#include "Database.h"

Database::Database() {
	this->doc = new tinyxml2::XMLDocument;
	cur_dep = nullptr;
	cur_emp = nullptr;
}

Database::Database(const Database& db) {
	this->file_name = db.file_name;
	this->doc = db.doc; // копируется именно указатель, а не значение, т.к. нет конструктора копий для значения
	this->cur_dep = db.cur_dep;
	this->cur_emp = db.cur_emp;
	this->departments = db.departments;
}

Database::~Database() {
	delete this->doc;
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
		// TODO

		//std::cout << root->Value() << std::endl;

		//tinyxml2::XMLElement* f = root->FirstChildElement();
		//std::cout << f->Attribute("name") << std::endl;

		//tinyxml2::XMLElement* f2 = root->FirstChildElement()->NextSiblingElement();
		//std::cout << f2->Attribute("name");
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
