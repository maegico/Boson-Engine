#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "Graphics.h"

//why does this need to be static
static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class WindowManager
{
public:
	WindowManager();
	WindowManager(const WindowManager& windowManagerCopy);
	~WindowManager();

	bool Init(HINSTANCE hInstance, int nCmdShow);
	void Run();

private:
	//leaving these as variables so that they can be changed
	int m_ScreenWidth, m_ScreenHeight;
	int m_PosX, m_PosY;
	//handle for window
	HWND m_HWnd;
	Graphics* m_Graphics;

	//not sure if I should make this return something in case of failure to create a window
	//also might change this since I am dealing with global variables
	void InitPriv(HINSTANCE hInstance, int nCmdShow);
	void FrameProcess();
};

#endif