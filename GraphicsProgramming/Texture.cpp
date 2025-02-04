#pragma once
#include "Texture.h"
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h> 
#include <iostream>
#include <string>


Texture::Texture()
{
	
}

void Texture::CreateTexture()
{
	glGenTextures(1, &textureID);

}

void Texture::SetImage(std::string file)//char* file)
{
	//Checks for SDL functionality
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL couldn't be initialised: " << SDL_GetError() << "\n";
		return;
	}

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
		std::cerr << "SDL_image couldn't be initialised: " << IMG_GetError() << "\n";
		SDL_Quit();
		return;
	}

	SDL_Surface* surface = IMG_Load(file.c_str());
	//32BIT PNGS verwenden!//
	

	if (!surface)
	{
		std::cerr << "\n\tMissing Texture! Couldn't be loaded from file.\n";
		std::cerr << IMG_GetError() << "\n\n";

		//IMG_Quit();
		//SDL_Quit();
		return;
	}

	glBindTexture(GL_TEXTURE_2D, textureID);

	//Texture filtering		//GL_NEAREST //GL_LINEAR //GL_LINEAR_MIPMAP_LINEAR //GL_NEAREST_MIPMAP_NEAREST //GL_NEAREST_MIPMAP_LINEAR //GL_LINEAR_MIPMAP_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Texture Wrapping		//GL_REPEAT //GL_CLAMP_TO_EDGE //GL_CLAMP_TO_BORDER //GL_MIRRORED_REPEAT

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(surface);

	//
	//IMG_Quit();
	//SDL_Quit();
}

void Texture::ClearFromRAM()
{
	glDeleteTextures(1, &textureID);
}
