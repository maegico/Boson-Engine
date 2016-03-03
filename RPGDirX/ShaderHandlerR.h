#include <string>

struct ShaderInfo
{
	std::string name;
	std::string shaderType;
	std::string shaderVersion;
};

struct LShaderInfo
{
	LPCWSTR name;
	LPCSTR shaderType;
	LPCSTR shaderVersion;
};

LShaderInfo shaderInfoToLShaderInfo(ShaderInfo shaderInfo)
{
	LShaderInfo lInfo;
	/*{
		
		/*convertStrToWSTR(shaderInfo.name),
		convertStrToWSTR(shaderInfo.shaderType),
		convertStrToWSTR(shaderInfo.shaderVersion)*/
	//};

	mbstowcs(lInfo.name, shaderInfo.name.c_str(), strlen(shaderInfo.name.c_str()));
	mbstowcs(lInfo.shaderType, shaderInfo.shaderType.c_str(), strlen(shaderInfo.shaderType.c_str()));
	mbstowcs(lInfo.shaderVersion, shaderInfo.shaderVersion.c_str(), strlen(shaderInfo.shaderVersion.c_str()));
	return lInfo;
}

/*std::wstring convertStrToWSTR(const std::string& s)
{
	int len;
	int sLength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), sLength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), sLength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}*/