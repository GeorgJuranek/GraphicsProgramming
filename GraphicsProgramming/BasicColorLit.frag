#version 460

in vec3 positionOut;
//in vec3 normalOut;
//in vec4 colorOut;
in vec2 uvOut;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    vec4 textureColor = texture(texture1, uvOut);
//    vec4 textureColor = vec4(0.0, 1.0, 0.0, 1.0);

    FragColor = textureColor;//vec4(uvOut.x, uvOut.y, 1, 1);//textureColor;//vec4(1,1,1,1);//textureColor * colorOut;
}


