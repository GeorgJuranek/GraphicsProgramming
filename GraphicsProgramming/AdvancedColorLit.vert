#version 460

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 shininess;
};

uniform Light light;
uniform Material material;

in vec4 colorIn;
in vec3 positionIn;
out vec4 colorOut;

void main(void)
{
	colorOut = vec4(light.ambient, 1)*colorIn; 
	gl_Position = vec4(positionIn, 1.0);
}