#include <windows.h> //SetConsoleOutputCP(CP_UTF8);


#include "Application.h"

int main() {
	// Нормальное отображение юникода
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_CTYPE, "UTF-8"); 

	const std::string xml_file_name = "data.xml";
	Application app;
	if (app.initialise(xml_file_name)) {
		app.work_with_user();
	}
}	
