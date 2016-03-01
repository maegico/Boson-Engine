#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <string>
#include <D3D11.h>
#include <D3DX11.h>

typedef int ShaderType;

class ShaderHandler
{
public:
	int LoadShader(ShaderType type, std::string& filename,
		std::string& function, std::string& model);
	ShaderHandler();
	~ShaderHandler();
};

#endif

