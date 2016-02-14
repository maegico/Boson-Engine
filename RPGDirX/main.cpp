#include "WindowManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WindowManager* windowManager;

	windowManager = new WindowManager();
	if (!windowManager)
		return 1;
	
	if (windowManager->Init(hInstance, nCmdShow))
		windowManager->Run();

	delete windowManager;

	return 0;
}