#ifndef SHADERPROGRAMH
#define SHADERPROGRAMH

struct ShaderProgram
{
public:
	ShaderProgram();
	unsigned int programId;
	ShaderProgram(char* vertexPath, char*fragmentPath);
	void SetAsActive();
	~ShaderProgram();
};


#endif // !SHADERPROGRAMH
