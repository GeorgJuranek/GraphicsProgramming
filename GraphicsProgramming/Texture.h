#pragma once
#include <GL/glew.h>

class Texture
{
public:
	Texture();
	void CreateTexture();
	void SetImage(char* file);
	void ClearFromRAM();
private:
	GLuint textureID;
};

