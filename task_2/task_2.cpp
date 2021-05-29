#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>

#include "tinyxml2.h"

#include "Department.h"
#include "Employment.h" 

//using namespace tinyxml2;

// Принимает u8 строку, выводит её пользователю
void print_to_user(const char* msg) {
	std::cout << msg << std::endl;
}


int main() {
	SetConsoleOutputCP(CP_UTF8); // Нормальное отображение кириллицы и вообще юникода
	
	const char* xml_file_name = "data.xml";
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError eResult = doc.LoadFile(xml_file_name);
	if (eResult != tinyxml2::XML_SUCCESS) {
		print_to_user(u8"Невозможно открыть файл!");
		return 1;
	}

	tinyxml2::XMLNode* root = doc.FirstChildElement();
	if (root == nullptr) {
		print_to_user(u8"Нет корневого элемента. Проверьте корректность .xml файла");
		return 1;
	}
	else {
		// TODO

		//std::cout << root->Value() << std::endl;

		//tinyxml2::XMLElement* f = root->FirstChildElement();
		//std::cout << f->Attribute("name") << std::endl;

		//tinyxml2::XMLElement* f2 = root->FirstChildElement()->NextSiblingElement();
		//std::cout << f2->Attribute("name");
	}



}
