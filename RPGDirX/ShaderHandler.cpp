#include "ShaderHandler.h"


ShaderHandler::ShaderHandler()
{
}


ShaderHandler::~ShaderHandler()
{
}

/*int ShaderHandler::LoadShader(ID3D11Device* device, ShaderType type, std::string& filename,
	std::string& function, std::string& model)
{
	HRESULT result = S_OK;

	ID3DBlob* compiledShaderBlob = NULL;
	ID3DBlob* errorMessagesBlob = NULL;

	//might still need this
	std::wstring fileNameTemp = convertStrToWSTR(filename);

	//switching tutorials
	if ( FAILED( result = D3DX11CompileFromFile(
		fileNameTemp.c_str(),	//shader file name
		0,
		0,
		function.c_str(),	//shader function name
		model.c_str(),		//shader file type
		0,
		0,
		0,
		&compiledShaderBlob,
		&errorMessagesBlob,
		&result
		) ) )
	{
		if (errorMessagesBlob != NULL)
		{
			//PRINT_ERROR_STRING();
			RELEASEMACRO(errorMessagesBlob);
			return false;
		}
	}

	result = device->CreateVertexShader(compiledShaderBlob->GetBufferPointer(),
										compiledShaderBlob->GetBufferSize(),
										NULL,
										&vertexShader);
	return 0;
}*/

//http://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode
//going to go through this more indepth
std::wstring ShaderHandler::convertStrToWSTR(const std::string& s)
{
	int len;
	int sLength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), sLength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), sLength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
