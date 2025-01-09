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
in vec3 normalOut;
in vec4 colorOut;
in vec2 uvOut;  // Die UV-Koordinaten aus dem Vertex-Shader

out vec4 FragColor;

uniform sampler2D texture1;  // Textur

void main()
{
    // Textur abtasten mit den UV-Koordinaten
    vec4 textureColor = texture(texture1, uvOut);

    // Kombiniere die Texturfarbe mit der berechneten Beleuchtung
    FragColor = textureColor * colorOut;
}
