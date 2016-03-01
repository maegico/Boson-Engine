#include "ShaderHandler.h"


ShaderHandler::ShaderHandler()
{
}


ShaderHandler::~ShaderHandler()
{
}

int ShaderHandler::LoadShader(ShaderType type, std::string& filename,
	std::string& function, std::string& model)
{
	HRESULT result = S_OK;

	ID3DBlob* compiledShader = NULL;
	ID3DBlob* errorMessages = NULL;

	if ( FAILED( result = D3DX11CompileFromFile(
		filename.c_str(),	//shader file name
		0,
		0,
		function.c_str(),	//shader function name
		model.c_str(),		//shader file name ???
		0,
		0,
		0,
		&compiledShader,
		&errorMessages,
		&result
		) ) )
	{
		//s
	}
}
