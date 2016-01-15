#version 330 core

in vec4 position;
in vec3 colors;

out vec4 ColorOut;

void main(void)
{
	if(position.y>0.0)
		ColorOut=vec4(1.0,1.0,1.0,1.0);
	else
		ColorOut=vec4(colors,1.0);
}