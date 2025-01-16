#version 460

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	//lightdamping
	float attenuationConst;
	float attenuationLinear;
	float attenuationQuad;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;
uniform vec3 cameraPosition;
uniform Light light;


in vec3 positionIn;
in vec3 normalIn;
//in vec4 colorIn;
in vec2 uvIn;//

out vec3 positionOut;
out vec3 normalOut;
//out vec4 colorOut;
out vec2 uvOut;//


uniform mat4 model;
uniform mat4 mvp;
uniform mat3 normal;

void main(void)
{
	positionOut = (model * vec4(positionIn, 1.0)).xyz;
	normalOut = normal*normalIn;

//	vec3 lightVector = normalize(light.position - positionOut);
//
//
////	//light damping // Attenuation
////	float distance = length(light.position - positionOut);
////	float attenuation = 1.0 / (light.attenuationConst + light.attenuationLinear * distance + light.attenuationQuad * distance * distance);
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
//
//	//Result//
//	vec3 lighting = ambientLight + diffuseLight + specularLight;
//
//	//colorOut = vec4(lighting, 1.0);
	uvOut = uvIn;//
//	//colorOut = colorIn*vec4(lighting,0);
//colorOut = colorIn;
	gl_Position = mvp * vec4(positionIn, 1.0);

}