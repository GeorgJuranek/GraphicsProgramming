#include "ConsoleLoger.h"
#include <iostream>
#include <windows.h>

//#include "Light.h"
//#include "Mesh.h"
//#include "Camera.h"

void ConsoleLoger::Init()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

	if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) 
	{
		consoleRowStart = consoleInfo.dwCursorPosition.Y;
		//consoleRowEnd = consoleRowStart + 6;
	}
}

void ConsoleLoger::DisplayPositionsUpdate(Light* light, Mesh mesh, Camera* camera, bool isInInsideMode)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD position;
    position.X = 0;
    position.Y = consoleRowStart;

    if (!SetConsoleCursorPosition(hConsole, position)) {
        std::cerr << "Error while setting cursor position in console.";
    }
    else
    {
        std::cout << "#TRANSFORMS#:\n";
	    std::cout << ">Light Position: " << light->position.x << " / " << light->position.y << " / " << light->position.z << '\n';
	    std::cout << ">Camera Position: " << camera->position.x << " / " << camera->position.y << " / " << camera->position.z << '\n';
	    std::cout << ">Object Rotation: " << mesh.GetRotation().x << " / " << mesh.GetRotation().y << " / " << mesh.GetRotation().z << '\n';
        std::cout << "\n";
        std::cout << "Is in inside-mode: " << (isInInsideMode ? "Yes" : "No ");
        std::cout << "\n";
    }

    //BUG NOTE:
    /*
    the Program freezes when cursor position is changed manually in 
    console window and then clicked on window to enter inside-mode (no mouse rotation or anything possible).
    Can only be closed when (for example) i call the task manager, so i get the cursor back and then quit it through visualstudio
    */
}