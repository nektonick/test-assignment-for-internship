#include <windows.h> //SetConsoleOutputCP(CP_UTF8);


#include "Application.h"

int main() {
	SetConsoleOutputCP(CP_UTF8); // Нормальное отображение кириллицы и вообще юникода

	const std::string xml_file_name = "data.xml";
	Application app;
	if (app.initialise(xml_file_name)) {
		app.work_with_user();
	}
}
