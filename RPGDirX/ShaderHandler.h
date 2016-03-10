#include <fstream>
#include <string>

struct ShaderInfo
{
	char* file;
	char* shaderType;
	char* shaderVersion;
};

inline char* loadTextFile(const char* file)
{
	std::ifstream inFile(file, std::ios::binary);
	//checks if the file is in the stream
	if (inFile.is_open())
	{
		//go to the end of the file
		inFile.seekg(0, std::ios::end);
		//finds the length of the file and saves it
		int length = (int)inFile.tellg();
		//goes back to the beginning
		inFile.seekg(0, std::ios::beg);

		char* fileContents = new char[length + 1];

		//grab the characters from the stream and put them in file Contents
		inFile.read(fileContents, length);
		//ends the file in a zero
		fileContents[length] = 0;
		//closes the file
		inFile.close();

		return fileContents;
	}
	else
		return 0;
}

inline bool loadShader(const char* file)
{
	//LShaderInfo lShaderInfo = shaderInfoToLShaderInfo(shaderInfo);

	//call the above function and save it into loadedFile
	const char* loadedFile = loadTextFile(file);

	//if something happens and it doesn't read in the file
	if (loadedFile == NULL)
	{
		//write the problem to the console and return 0
		printf("PROBLEM: Loaded File returned NULL\n");
		return false;
	}

}