#include "Graphics.h"


Graphics::Graphics()
{
}


Graphics::~Graphics()
{
	//switch to windowed mode
	mSwapChain->SetFullscreenState(FALSE, NULL);

	RELEASEMACRO(mSwapChain);
	RELEASEMACRO(mBackBuffer);

	//Restore default device settings
	if (mDevCon)
		mDevCon->ClearState();

	RELEASEMACRO(mDevCon);
	RELEASEMACRO(mDev);
}

ID3D11Device* Graphics::getDevicePtr()
{
	return mDev;
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
		&mSwapChain,
		&mDev,
		NULL,
		&mDevCon);

#ifdef DEBUG
	if (FAILED(result))
		return false;
#endif

	
	//Set the render target

	//create a texture using the back buffer
	ID3D11Texture2D* texture2D;
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&texture2D);

	//create a render target object (backBuffer)
	mDev->CreateRenderTargetView(texture2D, NULL, &mBackBuffer);
	texture2D->Release();

	//sets the render target as the back buffer
	mDevCon->OMSetRenderTargets(1, &mBackBuffer, NULL);

	//Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = screenWidth;
	viewport.Height = screenHeight;

	mDevCon->RSSetViewports(1, &viewport);
	
	return true;
}

void Graphics::RenderFrame()
{
	//clear the back buffer to a blue
	const FLOAT backColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	mDevCon->ClearRenderTargetView(mBackBuffer, backColor);

	//do 3D rendering here

	//switch the back buffer and the front buffer
	mSwapChain->Present(0, 0);
}

bool Graphics::compileShader(ShaderInfo* shader)
{
#ifdef DEBUG
	if (shader == NULL)
	{
		printf("PROBLEM: ShaderInfo struct = nullpointer\n");
		return false;
	}
#endif

	HRESULT result = S_OK;

	ID3DBlob* compiledShaderBlob = NULL;
	ID3DBlob* errorMessagesBlob = NULL;
	
	const char* loadedFile = loadTextFile(shader->file);

#ifdef DEBUG
	//if something happens and it doesn't read in the file
	if (loadedFile == NULL)
	{
		//write the problem to the console and return 0
		printf("PROBLEM: Loaded File returned NULL\n");
		return false;
	}
#endif

	//might have to do strlen()+1
	result = D3DCompile(
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
		&errorMessagesBlob);

#ifdef DEBUG
	if (FAILED(result))
	{
		if (errorMessagesBlob != NULL)
		{
			//use errorMessageBlob to print error
		}

		printf("PROBLEM: D3DCompile() failed.");
		return false;
	}
#endif
		
	//if vertex shader
	if (true)
		//last parameter is to a ID3D11 VertexShader
		result = mDev->CreateVertexShader(compiledShaderBlob->GetBufferPointer(), compiledShaderBlob->GetBufferSize(), NULL, NULL);
	else
		mDev->CreatePixelShader(compiledShaderBlob->GetBufferPointer(), compiledShaderBlob->GetBufferSize(), NULL, NULL);


	//shader reflection code below

	
	

	ID3D11ShaderReflection* shaderReflection = nullptr;
	result = D3DReflect(compiledShaderBlob->GetBufferPointer(), compiledShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&shaderReflection);

#ifdef DEBUG
	if (FAILED(result))
	{
		printf("PROBLEM: D3DReflect() failed.");
		return false;
	};
#endif

	//might use a ID3D11ShaderResourceView

	return true;
}

//http://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode
