#pragma once

//#include "SDL.h"
#include <GL\glew.h>
#include <SDL.h>

class Framework
{
public:
	static int screenWidth;
	static int screenHeight;

	bool hasQuit;

	SDL_Window* window = nullptr;
	SDL_GLContext context = nullptr;

	unsigned Init();
	void SetAttributes();
	unsigned MakeWindow();
	unsigned CreateContext();
	void SwapWindow();
	void Close();

	void CheckForClosingEvents();

	//void EnableFaceCulling(GLenum);
	//void SetFrontfaceDirection(GLenum);
	//void EnableDepthTest();

	bool CheckForKeyEvents(SDL_KeyCode keyCode);

	static SDL_Keycode GetCurrentKeyCode();

};