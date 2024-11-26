#pragma once
class Texture
{
public:
	Texture();
	void CreateTexture();
	void SetImage(char* file);
	void ClearFromRAM();
private:
	GLuint textureID;
	//SDL_Surface* surface;
	/*int width;
	int height;*/
};

