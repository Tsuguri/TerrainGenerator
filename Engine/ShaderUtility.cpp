 #include "ShaderUtility.h"
#include <fstream>

void ShowError(char* text)
{
	printf(text);
}

int ShaderUtility::LoadShader(const char* vertexFilePath,const char* fragmentFilePath, bool debugMode)
{
	GLuint vertexShaderID = CompileShader(vertexFilePath, GL_VERTEX_SHADER, debugMode);

	if(vertexShaderID==0)
	{
		return 0;
	}
	GLuint fragmentShaderId = CompileShader(fragmentFilePath, GL_FRAGMENT_SHADER, debugMode);

	if(fragmentShaderId==0)
	{
		return 0;
	}

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderID);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	GLint success;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		ShowError("Unable to link shader");
		return 0;
	}
	/*glGetProgramiv(programId, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		const int maxInfoLogSize = 2048;
		GLchar infoLog[maxInfoLogSize];
		glGetProgramInfoLog(programId, maxInfoLogSize, NULL, infoLog);
		char error[maxInfoLogSize + 64] = "Warning. Shader Compilation Failed";
		strcat_s(error, (char*)infoLog);
		ShowError(error, MB_ICONERROR);
		return 0;
	}*/

	glUseProgram(programId);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderId);
	return programId;
}

char* ShaderUtility::LoadFile(const char* path,char* buffer,int bufferSize, bool debugMode)
{
	std::ifstream input(path);
	if (input.fail())
		return nullptr;
	input.read(buffer, bufferSize);
	if(input.eof())
	{
		std::streamsize loaded = input.gcount();
		input.close();
		buffer[loaded] = '\0';
		return buffer;
	}
	else
	{
		input.close();
		return nullptr;
	}
}

int ShaderUtility::CompileShader(const char* path, GLenum type, bool debugMode)
{
	const int maxCodeLength = 65535;

	char shaderCode[maxCodeLength] = "";
	if (LoadFile(path, &shaderCode[0], maxCodeLength, debugMode) == nullptr)
	{
		ShowError("Unable to read and parse shader");
		return 0;
	}
	else if (debugMode)
		ShowError(shaderCode);
	GLuint shaderId = glCreateShader(type);
	if (shaderId == 0)
		return 0;
	const GLchar* source[1];
	source[0] = shaderCode;
	glShaderSource(shaderId, 1, source,NULL);

	glCompileShader(shaderId);

	int success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		const int maxInfoLogSize = 2048;
		GLchar infoLog[maxInfoLogSize];
		glGetShaderInfoLog(shaderId, maxInfoLogSize, NULL, infoLog);
		char error[maxInfoLogSize + 64] = "Warning. Shader Compilation Failed";
		strcat_s(error, (char*)infoLog);
		ShowError(error);
	}
	else if (debugMode)
		ShowError("Shader compiled");
	return shaderId;

}

