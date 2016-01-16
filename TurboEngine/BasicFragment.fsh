#version 330 core

in vec4 position;
in vec3 normals;
in vec4 worldPosition;

uniform int lightType = 0;
uniform vec3 cameraPosition = vec3(1, 1, 1);
uniform vec3 lightDir = vec3(-1, -1, 0);
uniform vec3 lightColor = vec3(1,1,1);
uniform float ambientStrength=0.3f;
uniform float specularStrength=0.1f;
uniform float materialShininess=32;

out vec4 ColorOut;

void main(void)
{
vec3 color;
	if(lightType==0)
		color=normals;
	else if(lightType==1)
		color=vec3(0.7,0.7,0.7);
	else
		color=normalize(abs(cameraPosition));
	//ambient
	vec3 ambient = ambientStrength*lightColor;

	//diffuse
	vec3 norm = normalize(normals);
	vec3 dir = normalize(lightDir);
	float diff = max(dot(norm, dir), 0.0);
	vec3 diffuse = diff * lightColor;

	//specular
	vec3 viewDir = normalize(cameraPosition - worldPosition.xyz);
	vec3 halfwayDir = normalize(dir + viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), materialShininess);
	vec3 specular = lightColor * spec;
	vec3 result = (ambient+diffuse+specular)*color;
		ColorOut=vec4(result,1.0);
}