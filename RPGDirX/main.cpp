#include "WindowManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WindowManager* windowManager;
	bool result;

	windowManager = new WindowManager();
	if (!windowManager)
		return 1;
	
	result = windowManager->Init(hInstance, nCmdShow);
	if (result)
		windowManager->Run();

	delete windowManager;

	return 0;
}