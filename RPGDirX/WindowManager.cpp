#include "WindowManager.h"


WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{
	if (m_Graphics)
		delete m_Graphics;
}

bool WindowManager::Init(HINSTANCE hInstance, int nCmdShow)
{
	//bool result;
	
	m_ScreenWidth = 0;
	m_ScreenHeight = 0;

	InitPriv(hInstance, nCmdShow);

	m_Graphics = new Graphics();
	if (!m_Graphics)
		return false;

	//result = m_Graphics->InitD3D(m_HWnd, m_ScreenWidth, m_ScreenHeight);
	if (!m_Graphics->InitD3D(m_HWnd, m_ScreenWidth, m_ScreenHeight))
		return false;

	return true;
}

void WindowManager::InitPriv(HINSTANCE hInstance, int nCmdShow)
{
	m_ScreenWidth = 800;
	m_ScreenHeight = 600;

	m_PosX = (GetSystemMetrics(SM_CXSCREEN) - m_ScreenWidth) / 2;
	m_PosY = (GetSystemMetrics(SM_CYSCREEN) - m_ScreenHeight) / 2;

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

	RECT r = { 0, 0, m_ScreenWidth, m_ScreenHeight };
	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);


	/*m_HWnd = CreateWindowEx(NULL,
		L"Boson Engine",	//name of window class, must be the same as in wndClassX
		L"Boson Engine",	//title of window
		WS_OVERLAPPEDWINDOW,	//window style
		m_PosX,	//x position of window
		m_PosY,	//y position of window
		m_ScreenWidth,	//width of window
		m_ScreenHeight,	//height of window
		NULL,	//parent window
		NULL,	//menus
		hInstance,	//application handle
		NULL);	//multiple windows*/

	/*m_HWnd = CreateWindowEx(NULL,
		L"Boson Engine",	//name of window class, must be the same as in wndClassX
		L"Boson Engine",	//title of window
		WS_OVERLAPPEDWINDOW,	//window style
		CW_USEDEFAULT,	//x position of window	//CW_USEDEFAULT - lets windows decide where to place the window
		CW_USEDEFAULT,	//y position of window
		r.right - r.left,	//width of window
		r.bottom - r.top,	//height of window
		NULL,	//parent window
		NULL,	//menus
		hInstance,	//application handle
		NULL);	//multiple windows*/

	m_HWnd = CreateWindowEx(NULL,
		L"Boson Engine",	//name of window class, must be the same as in wndClassX
		L"Boson Engine",	//title of window
		WS_OVERLAPPEDWINDOW,	//window style
		m_PosX,	//x position of window
		m_PosY,	//y position of window
		r.right - r.left,	//width of window
		r.bottom - r.top,	//height of window
		NULL,	//parent window
		NULL,	//menus
		hInstance,	//application handle
		NULL);	//multiple windows

	if (!m_HWnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		//would have a return false here
		//think about changing engine structure
	}

	ShowWindow(m_HWnd, nCmdShow);
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
	m_Graphics->RenderFrame();
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