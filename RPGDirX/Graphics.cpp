#include "Graphics.h"


Graphics::Graphics()
{
}


Graphics::~Graphics()
{
	//switch to windowed mode
	m_SwapChain->SetFullscreenState(FALSE, NULL);

	RELEASEMACRO(m_SwapChain);
	RELEASEMACRO(m_BackBuffer);

	//Restore default device settings
	if (m_DevCon)
		m_DevCon->ClearState();

	RELEASEMACRO(m_DevCon);
	RELEASEMACRO(m_Dev);
}

ID3D11Device* Graphics::getDevicePtr()
{
	return m_Dev;
}

bool Graphics::InitD3D(HWND hWnd, int screenWidth, int screenHeight)
{
	bool result;

	//Initialize Direct3D

	//create and set default values in the struct
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	//fill the struct

	//number of back buffers
	scd.BufferCount = 1;
	//save color format to 32-bit (8bits per channel/value) color
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//back buffer screen width
	scd.BufferDesc.Width = screenWidth;
	//back buffer screen height
	scd.BufferDesc.Height = screenHeight;
	//how the swap chain is to be used
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//the window to use
	scd.OutputWindow = hWnd;
	//MSAA number
	scd.SampleDesc.Count = 4;
	//to use windowed mode
	scd.Windowed = true;
	//allows fullscreen switching using Alt + Enter
	//scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//method(lets machine decide graphics adapter, use hardware or software
		//used to set software code, flags,feature levels list, number in feature levels list,
		//SDK version, double pointer to swap chain description,
		//double pointer to swap chain, double pointer to device,
		//pointer to feature level var, double pointer to device context)
	result = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_SwapChain,
		&m_Dev,
		NULL,
		&m_DevCon);

	if (FAILED(result))
		return false;

	
	//Set the render target

	//create a texture using the back buffer
	ID3D11Texture2D* texture2D;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&texture2D);

	//create a render target object (backBuffer)
	m_Dev->CreateRenderTargetView(texture2D, NULL, &m_BackBuffer);
	texture2D->Release();

	//sets the render target as the back buffer
	m_DevCon->OMSetRenderTargets(1, &m_BackBuffer, NULL);

	//Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = screenWidth;
	viewport.Height = screenHeight;

	m_DevCon->RSSetViewports(1, &viewport);
	
	return true;
}

void Graphics::RenderFrame()
{
	//clear the back buffer to a blue
	const FLOAT backColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	m_DevCon->ClearRenderTargetView(m_BackBuffer, backColor);

	//do 3D rendering here

	//switch the back buffer and the front buffer
	m_SwapChain->Present(0, 0);
}

bool Graphics::compileShader(ShaderInfo* shader)
{
	HRESULT result = S_OK;

	ID3DBlob* compiledShaderBlob = NULL;
	ID3DBlob* errorMessagesBlob = NULL;
	
	const char* loadedFile = loadTextFile(shader->file);

	//if something happens and it doesn't read in the file
	if (loadedFile == NULL)
	{
		//write the problem to the console and return 0
		printf("PROBLEM: Loaded File returned NULL\n");
		return false;
	}

	//might have to do strlen()+1
	if ( FAILED( result = D3DCompile(
		(LPCVOID)loadedFile,
		strlen(loadedFile),
		NULL,
		NULL,
		NULL,
		shader->shaderType,
		shader->shaderVersion,
		NULL,
		NULL,
		&compiledShaderBlob,
		&errorMessagesBlob ) ) )
		return false;

	//shader reflection code below

	ID3D11ShaderReflection* shaderReflection = nullptr;
	if(FAILED(result = D3DReflect(compiledShaderBlob->GetBufferPointer(), compiledShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&shaderReflection)));


	return true;
}

//http://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode
