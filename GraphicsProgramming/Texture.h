#pragma once
#include <GL/glew.h>

#include <iostream>
#include <string>

class Texture
{
public:
	Texture();
	void CreateTexture();
	void SetImage(std::string file);//char* file);
	void ClearFromRAM();
private:
	GLuint textureID;
};

