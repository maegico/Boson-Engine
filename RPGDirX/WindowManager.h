#ifndef _WINDOW_MANAGER_H
#define _WINDOW_MANAGER_H

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "Graphics.h"

//why does this need to be static
static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class WindowManager
{
public:
	WindowManager();
	~WindowManager();

	bool Init(HINSTANCE hInstance, int nCmdShow);
	void Run();

private:
	//leaving these as variables so that they can be changed
	int mScreenWidth, mScreenHeight;
	int mPosX, mPosY;
	//handle for window
	HWND mHWnd;
	Graphics* mGraphics;

	//not sure if I should make this return something in case of failure to create a window
	//also might change this since I am dealing with global variables
	void InitPriv(HINSTANCE hInstance, int nCmdShow);
	void FrameProcess();
};

#endif