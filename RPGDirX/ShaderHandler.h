#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <string>
//#include <D3D11.h>
#include <D3DX11.h>
#include <D3Dcompiler.h>
#include "Graphics.h"

#pragma comment(lib, "D3Dcompiler.lib")

#define RELEASEMACRO(x) { if(x) { x->Release(); x = 0; } }

typedef int ShaderType;

class ShaderHandler
{
public:
	/*int LoadShader(ID3D11Device* device, ShaderType type, std::string& filename,
		std::string& function, std::string& model);*/
	std::wstring convertStrToWSTR(const std::string& s);
	ShaderHandler();
	~ShaderHandler();
};

#endif

