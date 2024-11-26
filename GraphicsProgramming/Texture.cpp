#include "Texture.h"
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h> 
#include <iostream>

void Texture::CreateTexture()
{
	glGenTextures(1, &textureID);

}

void Texture::SetImage(char* file)
{
	SDL_Surface* surface = IMG_Load(file);

	if (!surface)
	{
		std::cerr << "Missing Texture! Couldn't be loaded from file.";
		return;
	}

	//width = surface->w;
	//height = surface->h;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(surface);
	//glDeleteTextures(1, &textureID);
}

void Texture::ClearFromRAM()
{
	glDeleteTextures(1, &textureID);
}
