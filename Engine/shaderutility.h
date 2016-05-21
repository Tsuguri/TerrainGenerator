#ifndef SHADER_UTILITYH
#define SHADER_UTILITYH

#include <GL\glew.h>

class ShaderUtility
{
public:
	static int LoadShader(const char* vertexFilePath,const char* fragmentFilePath,bool debugMode=false);
private:
	static char* LoadFile(const char* path, char* buffer, int bufferSize, bool debugMode=false);
	static int CompileShader(const char* path, GLenum type, bool debugMode = false);
};


#endif
