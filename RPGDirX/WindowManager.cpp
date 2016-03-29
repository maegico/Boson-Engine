#include "WindowManager.h"


WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{
	if (mGraphics)
		delete mGraphics;
}

bool WindowManager::Init(HINSTANCE hInstance, int nCmdShow)
{
	//bool result;
	
	mScreenWidth = 0;
	mScreenHeight = 0;

	InitPriv(hInstance, nCmdShow);

	mGraphics = new Graphics();
	if (!mGraphics)
		return false;

	//result = mGraphics->InitD3D(mHWnd, mScreenWidth, mScreenHeight);
	if (!mGraphics->InitD3D(mHWnd, mScreenWidth, mScreenHeight))
		return false;

	return true;
}

void WindowManager::InitPriv(HINSTANCE hInstance, int nCmdShow)
{
	mScreenWidth = 800;
	mScreenHeight = 600;

	mPosX = (GetSystemMetrics(SM_CXSCREEN) - mScreenWidth) / 2;
	mPosY = (GetSystemMetrics(SM_CYSCREEN) - mScreenHeight) / 2;

	//struct with info for window class (extension of WNDCLASS)
	WNDCLASSEX wndClassX;
	ZeroMemory(&wndClassX, sizeof(WNDCLASSEX));

	//size of struct
	wndClassX.cbSize = sizeof(WNDCLASSEX);
	//style of the window
	wndClassX.style = CS_HREDRAW | CS_VREDRAW;
	//the message function
	wndClassX.lpfnWndProc = WndProc;
	//a handle to a copy of the application
	wndClassX.hInstance = hInstance;
	//window taskbar icon
	wndClassX.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	//the default mouse image
	wndClassX.hCursor = LoadCursor(NULL, IDC_ARROW);
	//the name of the window
	wndClassX.lpszClassName = L"Boson Engine";

	if (!RegisterClassEx(&wndClassX))
	{
		MessageBox(0, L"RegisterClass Failed", 0, 0);
		//would have a return false here
		//think about changing engine structure
	}

	RECT r = { 0, 0, mScreenWidth, mScreenHeight };
	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);

	mHWnd = CreateWindowEx(NULL,
		L"Boson Engine",	//name of window class, must be the same as in wndClassX
		L"Boson Engine",	//title of window
		WS_OVERLAPPEDWINDOW,	//window style
		mPosX,	//x position of window
		mPosY,	//y position of window
		r.right - r.left,	//width of window
		r.bottom - r.top,	//height of window
		NULL,	//parent window
		NULL,	//menus
		hInstance,	//application handle
		NULL);	//multiple windows

	if (!mHWnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		//would have a return false here
		//think about changing engine structure
	}

	ShowWindow(mHWnd, nCmdShow);
}

void WindowManager::Run()
{
	MSG msg;
	bool result;

	ZeroMemory(&msg, sizeof(MSG));

	//main loop
	while (true)
	{
		//check the message queue and see if there are any messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//translates the message format
			TranslateMessage(&msg);
			//send the message to the WndProc function
			DispatchMessage(&msg);

			//and if it is time to quit, quit
			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			//where the game code is run

			FrameProcess();
		}
	}
}

void WindowManager::FrameProcess()
{
	mGraphics->RenderFrame();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//check the message
	switch (uMsg)
	{
		//if it says to destroy the window
		case WM_DESTROY:
		{
			//close the application
			PostQuitMessage(0);
			return 0;
		}	break;
	}

	//Handles the rest of the messages
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}