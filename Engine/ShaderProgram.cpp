#include "ShaderProgram.h"
#include "ShaderUtility.h"

ShaderProgram::ShaderProgram()
{
	programId = 0;
}

ShaderProgram::ShaderProgram(const char * vertexPath, const char * fragmentPath)
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
