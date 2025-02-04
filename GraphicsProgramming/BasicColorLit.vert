#version 460


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

	uvOut = uvIn;//

	gl_Position = mvp * vec4(positionIn, 1.0);

}