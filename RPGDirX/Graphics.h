#ifndef _GRAPHICS_H
#define _GRAPHICS_H

//Will need to download the Windows Standalone SDK for Windows 10

#include <D3D11.h>
#include <d3dcompiler.h>
#include <string>
#include "ShaderHandler.h"

#define DEBUG
#define RELEASEMACRO(x) { if(x) { x->Release(); x = 0; } }

//include the library files
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3DX11.lib")
#pragma comment(lib, "D3dcompiler.lib")

class Graphics
{
public:
	Graphics();
	~Graphics();

	ID3D11Device* getDevicePtr();

	//sets up and initializes Direct3D
	bool InitD3D(HWND hWnd, int screenWidth, int screenHeight);
	void RenderFrame();
	void Shutdown();

private:
	//a bool to tell whether vsync is enabled
	bool mVsync_enabled;
	//an int to store the amount of dedicated video memory
	int mVideoCardMemory;
	//??
	char mVideoCardDesc[128];
	//pointer to swap chain interface
	IDXGISwapChain* mSwapChain;
	//pointer to Direct3D device interface
	ID3D11Device* mDev;
	//pointer to Direct3D device context
	ID3D11DeviceContext* mDevCon;
	//a pointer to the render target
	ID3D11RenderTargetView* mBackBuffer;

	//bool loadShader(ShaderInfo shaderInfo);
	bool compileShader(ShaderInfo* shader);
};

#endif