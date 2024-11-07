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

//in vec4 colorOut;
out vec4 pixelColor;

void main(void)
{
	//pixelColor = colorOut;
	pixelColor = vec4(1.0, 1.0, 1.0, 1.0);
}
