#include "ShaderProgram.h"
#include "ShaderUtility.h"

ShaderProgram::ShaderProgram()
{
	programId = 0;
}

ShaderProgram::ShaderProgram(char * vertexPath, char * fragmentPath)
{
	programId = ShaderUtility::LoadShader(vertexPath, fragmentPath);
}

void ShaderProgram::SetAsActive()
{
	glUseProgram(programId);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programId);
}
