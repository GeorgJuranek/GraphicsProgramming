#include "Framework.h"

#include "Framework.h"
#include "GL\glew.h"
#include <iostream>

#include "Error.h"


unsigned Framework::Init()
{
	int error = SDL_Init(SDL_INIT_EVERYTHING);
	Error::CheckError(error, "Framework failed to init");

	SetAttributes();

	error = MakeWindow();
	Error::CheckError(error, "Framework failed to make window");

	error = CreateContext();
	Error::CheckError(error, "Framework failed to create Context");

	error = glewInit();
	Error::CheckError(error, "Framework failed to init glew");
	
	return 0;
};

void Framework::SetAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
}

unsigned Framework::MakeWindow()
{
	window = SDL_CreateWindow("Graphics Programming",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_OPENGL);

	if (window == nullptr)
	{
		std::cerr << "Window creation has not worked!";
		return 100;
	}

	return 0;
}

unsigned Framework::CreateContext()
{
	SDL_GLContext context = nullptr;
	context = SDL_GL_CreateContext(window);

	if (context == nullptr)
	{
		std::cerr << "Context didint worked!";
		return 100;
	}
	else
	{
		return 0;
	}
};

void Framework::SwapWindow()
{

}

void Framework::Close()
{
	SDL_Event events;
	bool quit = false;

	while (quit == false)
	{
		while (SDL_PollEvent(&events))
		{
			switch (events.type)
			{
			case SDL_QUIT: //-> (x)
				quit = true;
				break;


			case SDL_KEYDOWN: 
				if (events.key.keysym.sym == SDLK_ESCAPE) //-> ESC
				{
					quit = true;
				}
				break;

			default:
				break;
			}
		}
	}

	SDL_GL_SwapWindow(window);
	//SDL_DestroyWindow(window);
};







