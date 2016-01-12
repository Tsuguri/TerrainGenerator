#version 330 core

layout(location = 0)in vec3 positionIn;
layout(location = 3)in vec4 colorIn;

const mat4 IdMat = mat4(1.0);
uniform mat4 ModelMat = IdMat;
uniform mat4 ViewMat = IdMat;
uniform mat4 ProjMat = IdMat;
mat4 MVP = ProjMat*ViewMat*ModelMat;

out vec4 position;
out vec4 colors;

void main(void)
{
	position = vec4(positionIn, 1.0);
	gl_Position = MVP*position;
	position = ModelMat*position;
	colors = colorIn;

}