#version 460

//struct Light
//{
//	vec3 position;
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//};
//
//uniform Light light;
//in vec4 colorIn;
//in vec3 positionIn;
//out vec4 colorOut;
//
//void main(void)
//{
//	colorOut = vec4(light.ambient, 1)*colorIn; 
//	gl_Position = vec4(positionIn, 1.0);
//}


//

in vec3 positionIn;
in vec3 normalIn;

out vec3 positionOut;

out vec3 normalOut;

uniform mat4 model;
uniform mat4 mvp;
uniform mat3 normal;

void main(void)
{
	positionOut = (model * vec4(positionIn, 1.0)).xyz;
	normalOut = normal*normalIn;
	gl_Position = mvp * vec4(positionIn, 1.0);
}