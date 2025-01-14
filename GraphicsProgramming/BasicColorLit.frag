//#version 460
//
//in vec4 colorOut;
//out vec4 pixelColor;
//
//void main(void)
//{
//	pixelColor = colorOut;
//}




//
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

    FragColor = textureColor;//vec4(uvOut.x, uvOut.y, 1, 1);//textureColor;//vec4(1,1,1,1);//textureColor * colorOut;
}


