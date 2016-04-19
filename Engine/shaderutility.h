#ifndef SHADER_UTILITYH
#define SHADER_UTILITYH

#include <GL\glew.h>

class ShaderUtility
{
public:
	static int LoadShader(char* vertexFilePath, char* fragmentFilePath,bool debugMode=false);
private:
	static char* LoadFile(char* path, char* buffer, int bufferSize, bool debugMode=false);
	static int CompileShader(char* path, GLenum type, bool debugMode = false);
};


#endif
