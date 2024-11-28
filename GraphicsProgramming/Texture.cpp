#pragma once
#include "Texture.h"
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h> 
#include <iostream>

//GLuint textureID;

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

	//Texture filtering		//GL_NEAREST //GL_LINEAR //GL_LINEAR_MIPMAP_LINEAR //GL_NEAREST_MIPMAP_NEAREST //GL_NEAREST_MIPMAP_LINEAR //GL_LINEAR_MIPMAP_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	//Texture Wrapping		//GL_REPEAT //GL_CLAMP_TO_EDGE //GL_CLAMP_TO_BORDER //GL_MIRRORED_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(surface);
	glDeleteTextures(1, &textureID);
}

void Texture::ClearFromRAM()
{
	glDeleteTextures(1, &textureID);
}
