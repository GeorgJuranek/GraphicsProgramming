#version 460

//struct Light
//{
//	vec3 position;
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//
//	//lightdamping
//	float attenuationConst;
//	float attenuationLinear;
//	float attenuationQuad;
//};
//
//struct Material
//{
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//	float shininess;
//};
//
//uniform Material material;
//uniform vec3 cameraPosition;
//uniform Light light;


layout(location = 0) in vec3 positionIn;
layout(location = 1) in vec4 colorIn;
layout(location = 2) in vec2 uvIn;//
layout(location = 3) in vec3 normalIn;

layout(location = 4) out vec3 positionOut;
layout(location = 5) out vec4 colorOut;
layout(location = 6) out vec2 uvOut;//
layout(location = 7) out vec3 normalOut;


//uniform mat4 model;
layout(location = 8) uniform mat4 mvp;
layout(location = 9) uniform mat3 normal;

void main(void)
{
	positionOut = (mvp * vec4(positionIn, 1.0)).xyz; //feedback marcus: use mvp instead of model
	normalOut = /*normal**/normalIn; //feedback marcus: ersetzen mit mat3(transpose(inverse(mvp))) *


//	//FEEDBACK MARCUS: put lightstuff in frag-shader//
//	vec3 lightVector = normalize(light.position - positionOut);
//
//	//light damping // Attenuation
//	float distance = length(light.position - positionOut);
//	float attenuation = 1.0 / (light.attenuationConst + light.attenuationLinear * distance + light.attenuationQuad * distance * distance);
//
//	//Ambient//
//	vec3 ambientLight = light.ambient;
//
//	//Diffuse//
//	float diffuseFactor = max(dot(normalOut, lightVector), 0.0);
//	vec3 diffuseLight = light.diffuse * diffuseFactor;
//
//	//Specular//	
//	vec3 viewVector = normalize(cameraPosition - positionOut);
//	vec3 reflectionVector = reflect(-lightVector, normalOut);
//	float specularFactor = pow(max(dot(reflectionVector, viewVector), 0.0), material.shininess);
//	vec3 specularLight = light.specular * material.specular * specularFactor;
//
//	//Result//
//	vec3 lighting = ambientLight + diffuseLight + specularLight;
//	

	colorOut = colorIn;

	//colorOut = vec4(lighting, 1.0);

	uvOut = uvIn;

	//colorOut = colorIn*vec4(lighting,0);

	gl_Position = mvp * vec4(positionIn, 1.0);

}