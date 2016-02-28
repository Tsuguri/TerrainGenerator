#version 330 core

layout(location = 0)in vec3 positionIn;
layout(location = 3)in vec3 normalIn;

const mat4 IdMat = mat4(1.0);
uniform mat4 ModelMat = IdMat;
uniform mat4 ViewMat = IdMat;
uniform mat4 ProjMat = IdMat;
mat4 MVP = ProjMat*ViewMat*ModelMat;
mat3 NormalMat = mat3(transpose(inverse(ModelMat)));

out vec4 position;
out vec3 normals;
out vec4 worldPosition;

void main(void)
{
	position = vec4(positionIn, 1.0);
	worldPosition = ModelMat*position;
	gl_Position = MVP*position;
	position = ModelMat*position;
	normals = NormalMat*normalIn;
}