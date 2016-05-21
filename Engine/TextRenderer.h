#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H  
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <map>
#include "ShaderProgram.h"
#include "TextInfo.h"
#include <vector>

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

class TextRenderer
{
	static TextRenderer* renderer;
	GLuint VAO;
	GLuint VBO;
	ShaderProgram* program;
	std::map<GLchar, Character> Characters;
	GLuint shader;
	int width, height;
	void InitializeCharacters(const char* fontPath);
	void TextRenderer::RenderSingle(TextInfo info);
	std::vector<TextInfo> textes;
public:
	static TextRenderer* Get();
	TextRenderer(const char* fontPath,const char* vertexPath, const char* fragmentPath);
	void TextRenderer::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	void Render();
	void SetScreenSize(int width, int height);
};
