#ifndef SHADERPROGRAMH
#define SHADERPROGRAMH

struct ShaderProgram
{
public:
	ShaderProgram();
	unsigned int programId;
	ShaderProgram(const char* vertexPath,const char*fragmentPath);
	void SetAsActive();
	~ShaderProgram();
};


#endif // !SHADERPROGRAMH
