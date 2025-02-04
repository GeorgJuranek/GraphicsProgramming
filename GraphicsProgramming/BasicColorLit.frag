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

uniform Light light;
uniform Material material;
uniform vec3 cameraPosition;



in vec3 normalOut;
in vec3 positionOut;
in vec2 uvOut;

uniform sampler2D texture1;

out vec4 FragColor;

vec3 calculateAmbient(Light light, Material material)
{
	return light.ambient * material.ambient;
}

vec3 calculateDiffuse(Light light, Material material)
{
	vec3 normal = normalize(normalOut);
	vec3 lightDirection = normalize(light.position - positionOut);
	float lightIntensity = max(dot(lightDirection, normal), 0.0);

	return light.diffuse * material.diffuse * lightIntensity;
}

vec3 calculateSpecular(Light light, Material material)
{
	vec3 normal = normalize(normalOut);
	vec3 lightDirection = normalize(light.position - positionOut);
	vec3 viewDirection = normalize(cameraPosition - positionOut);
	vec3 reflection = reflect(-lightDirection, normal);
	float specularTerm = pow(max(dot(viewDirection, reflection), 0.0), material.shininess);

	return light.specular * material.specular * specularTerm;
}

float calculateAttenuation(Light light)
{
	float distance = length(light.position - positionOut);
	return
	(
		1.0/
		(
			light.attenuationConst + 
			(light.attenuationLinear * distance) + 
			(light.attenuationQuad * distance * distance)
		)
	);
}

void main()
{
	vec3 ambientColor = calculateAmbient(light, material);

	vec3 diffuseColor = calculateDiffuse(light, material);

	vec3 specularColor = calculateSpecular(light, material);

	float attenuation = calculateAttenuation(light);


	//vec4 color = vec4(attenuation * ((ambientColor + diffuseColor + specularColor)* 0.33f), 1.0);
	vec4 color = vec4(1,1,1,1);

	//gl_FragColor = color * texture(texture1, uvOut);

    FragColor = color * texture(texture1, uvOut);
}


