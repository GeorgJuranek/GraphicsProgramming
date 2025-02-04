#version 460

struct Light 
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
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
uniform sampler2D texture1;

in vec3 normalOut;
in vec3 positionOut;
in vec2 uvOut;

out vec4 FragColor;

//Ambient
vec3 calculateAmbient(Light light, Material material) 
{
    return light.ambient * material.ambient;
}

//Diffuse
vec3 calculateDiffuse(Light light, Material material, vec3 normal) 
{
    vec3 lightDirection = normalize(light.position - positionOut);
    float lightIntensity = max(dot(lightDirection, normal), 0.0);
    return light.diffuse * material.diffuse * lightIntensity;
}

//Specular
vec3 calculateSpecular(Light light, Material material, vec3 normal) 
{
    vec3 lightDirection = normalize(light.position - positionOut);
    vec3 viewDirection = normalize(cameraPosition - positionOut);
    vec3 reflection = reflect(-lightDirection, normal);
    float specularTerm = pow(max(dot(viewDirection, reflection), 0.0), material.shininess);
    return light.specular * material.specular * specularTerm;
}

//Attenuation
float calculateAttenuation(Light light) 
{
    float distance = length(light.position - positionOut);

    //Clamp attenuation, so it cant be <0. What was reason for almost all white after adding normals
    return clamp(1.0 / (light.attenuationConst + light.attenuationLinear * distance + light.attenuationQuad * distance * distance), 0.1, 1.0);
}

void main() 
{
    vec3 normal = normalize(normalOut);  // normalize the normals, in case normals are not normal
    vec3 ambientColor = calculateAmbient(light, material);
    vec3 diffuseColor = calculateDiffuse(light, material, normal);
    vec3 specularColor = calculateSpecular(light, material, normal);

    float attenuation = calculateAttenuation(light);

    vec3 finalColor = (ambientColor + diffuseColor + specularColor) * attenuation;
    
    // Combine Light an Texture
    FragColor = vec4(finalColor, 1.0) * texture(texture1, uvOut);
}
