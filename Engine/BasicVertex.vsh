#version 330 core

layout(location = 0)in vec3 positionIn;
layout(location = 2)in vec3 triangleCenter;
layout(location = 1)in vec3 standardNormal;
layout(location = 3)in vec3 normalIn;

const mat4 IdMat = mat4(1.0);
uniform vec3 defaultColor = vec3(0.7);


uniform mat4 ModelMat = IdMat;
uniform mat4 ViewMat = IdMat;
uniform mat4 ProjMat = IdMat;

uniform int lightType = 0;
uniform vec3 cameraPosition = vec3(1, 1, 1);
uniform vec3 lightDir = vec3(-1, -1, 0);
uniform vec3 lightColor = vec3(1, 1, 1);

uniform float ambientStrength = 0.3f;
uniform float specularStrength = 0.1f;
uniform float materialShininess = 32;

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
	if (lightType == 0)
	{
		normals = NormalMat*normalIn;
	}
	else
	{
		vec3 ambient = ambientStrength*lightColor;
		vec3 dir = normalize(lightDir);
		vec3 norm;
		vec3 viewDir;
		if (lightType == 1)
		{
			norm = normalize(NormalMat*standardNormal);
			viewDir = normalize(cameraPosition - (ModelMat*vec4(triangleCenter,1)).xyz);
		}
		else
		{
			norm = normalize(NormalMat*normalIn);
			viewDir = normalize(cameraPosition - (worldPosition).xyz);
		}
		float diff = max(dot(norm, dir), 0.0);
		vec3 diffuse = diff * lightColor;
		vec3 halfway = normalize(dir + viewDir);
		float spec = pow(max(dot(norm, halfway), 0.0), materialShininess);
		vec3 specular = lightColor * spec;
		normals =(ambient + diffuse +specular)*defaultColor;
		
	}
}