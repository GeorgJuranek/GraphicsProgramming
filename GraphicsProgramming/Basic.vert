#version 460

in vec3 positionIn;
in vec3 colorIn;
out vec3 colorOut;

void main(void)
{
	colorOut = colorIn;
	gl_Position = vec4(positionIn, 1.0);
}