#ifndef _GRAPHICS_H
#define _GRAPHICS_H

//direct3D 11 header file
#include <D3D11.h>
//direct3D file extensions header
#include <D3DX11.h>
//allows use of pragma comment below
#include <D3DX10.h>

#define RELEASEMACRO(x) { if(x) { x->Release(); x = 0; } }

//include the library files
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3DX11.lib")
#pragma comment(lib, "D3DX10.lib")

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
	bool m_Vsync_enabled;
	//an int to store the amount of dedicated video memory
	int m_VideoCardMemory;
	//??
	char m_VideoCardDesc[128];
	//pointer to swap chain interface
	IDXGISwapChain* m_SwapChain;
	//pointer to Direct3D device interface
	ID3D11Device* m_Dev;
	//pointer to Direct3D device context
	ID3D11DeviceContext* m_DevCon;
	//a pointer to the render target
	ID3D11RenderTargetView* m_BackBuffer;
	//why is a texture the depth stencil buffer
	ID3D11Texture2D* m_DepthStencilBuffer;
	ID3D11DepthStencilState* m_DepthStencilState;
	ID3D11DepthStencilView* m_DepthStencilView;
	ID3D11RasterizerState* m_rasterState;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_orthoMatrix;
};

#endif