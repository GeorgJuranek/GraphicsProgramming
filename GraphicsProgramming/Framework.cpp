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
	
	SetFrontfaceDirection(GL_CCW);
	EnableFaceCulling(GL_BACK);
	EnableDepthTest();

	GLenum glewStatus = glewInit();
	if (glewStatus != GLEW_OK)
	{
		std::cerr << "GLEW Error:" << glewGetErrorString(glewStatus) << "\n";
	}

	if (window != nullptr)
		std::cout << "Created window" << '\n';

	if (context != nullptr)
		std::cout << "Created Context" << '\n';
	
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
	SDL_GL_SwapWindow(window);
}

void Framework::Close()
{
	if (context != nullptr)
		SDL_GL_DeleteContext(context);

	if (window != nullptr)
		SDL_DestroyWindow(window);
	
	SDL_Quit();
}

void Framework::CheckForClosingEvents() //obsolete
{
	SDL_Event events;

	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{
		case SDL_QUIT: //-> (x)
			hasQuit = true;
			break;


		case SDL_KEYDOWN: 
			if (events.key.keysym.sym == SDLK_ESCAPE) //-> ESC
			{
				hasQuit = true;
			}
			break;

		default:
			break;
		}
	}
};


bool Framework::CheckForKeyEvents(SDL_KeyCode keyCode) //obsolete
{
	SDL_Event events;

	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_KEYDOWN:
			if (events.key.keysym.sym == keyCode)
			{
				return true;
			}

		default:
			return false;
		}
	}
};

SDL_Keycode Framework::GetCurrentKeyCode() //obsolete
{
	SDL_Event events;

	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_KEYDOWN:
			return events.key.keysym.sym;
		}
	}

	return SDLK_UNKNOWN;
};


void Framework::EnableFaceCulling(GLenum faceType)
{
	glEnable(GL_CULL_FACE); //activate cullingmodus-state for faces
	glCullFace(faceType);
}

void Framework::SetFrontfaceDirection(GLenum faceDirection)
{
	glFrontFace(faceDirection);
}

void Framework::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST); //clockwise or not clockwise indices drawing
	//glDepthFunc(GL_GEQUAL);
}

void Framework::ClearWindow()
{

}

void Framework::SetClearColor(float, float, float, float)
{

};







