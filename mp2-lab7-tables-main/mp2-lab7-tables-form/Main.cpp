#include "TablesForm.h"
#include <Windows.h> 
using namespace mp2lab7tablesform;

[STAThread]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew TablesForm);
	return 0;
}