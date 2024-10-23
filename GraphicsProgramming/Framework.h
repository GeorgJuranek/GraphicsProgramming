#pragma once

#include "SDL.h"
#include <GL\glew.h>
#include <SDL.h>

class Framework
{
public:
	static int screenWidth;
	static int screenHeight;

	bool hasQuit;

	SDL_Window* window;
	SDL_GLContext context;

	unsigned Init();
	void SetAttributes();
	unsigned MakeWindow();
	unsigned CreateContext();
	void SwapWindow();
	void CheckForClosingEvents();

	//void EnableFaceCulling(GLenum);
	//void SetFrontfaceDirection(GLenum);
	//void EnableDepthTest();

};