#include <iostream>

#include "Framework.h"
#include "Shader.h"
#include "Light.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"

#include <string>

int main(int argc, char* argv[])
{


	//The FRAMEWORK creates the window and the openGL context
	Framework* framework = new Framework();
    framework->Init();

	//The LIGHT
	Light* light = new Light();
	light->Init();

	//The SHADER creates the shaderProgram from the .vert(vertices) and .frag(fragment =color) glsl code
	Shader* shader = new Shader();
	shader->Init("BasicColorLit.vert", "BasicColorLit.frag"); //shader->Init("Basic.vert", "Basic.frag"); 

	//The MATERIAL only holds information for the lighting (ambient, diffuse,...)
	Material* material = new Material();

	//The MESH creates the Buffers for itself (as vbo and gives it to vao)
	//Gets necessary information from shader and material
	//Can Draw itself dependent from light and camera
	//Holds transformations like rotate,translate, scale
	Mesh mesh;
	mesh.Init(shader, material, "C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/basicCube.obj");

	//Texture
	Texture* texture = new Texture();
	texture->CreateTexture();
	texture->SetImage("C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Textures/car.png");//C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Textures/car");//C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Textures/car.png");//"C:\\Users\\Georg\\Desktop\\GraphicsProgramming\\GraphicsProgramming\\Textures\\BricksTexture.png");


	//The CAMERA
	Camera* camera = new Camera();
	camera->Init();


	//Infos to Console
    std::cout << "Graphics Programming Console:\n";
	std::cout << "Hold 'r' to rotate the object.\n";
	std::cout << "Use 'W'A'S'D' Arrow-keys to move the light.\n";
	std::cout << "Use 'W'A'S'D' to move the camera.\n";
	std::cout << "Click in the Window to go into 'Inside-mode'.\n";
	std::cout << "Use 'Esc' to leave inside-mode and tap another time to close viewer.\n";

	glClearColor(1, 0.33, 0.33, 1);

	// LOOP //
	while (!framework->hasQuit)
	{

		// RENDERING //

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (light == nullptr || camera == nullptr)
			std::cerr << "No light or camera was found during renderloop!\n";
		else
			mesh.Draw(light, camera);

		if (framework->window != nullptr)
			framework->SwapWindow();
		else
			std::cerr << "framework window is missing";


		//Transformation Tests

		SDL_Event events;
		while (SDL_PollEvent(&events))
		{
			switch (events.type)
			{
			case SDL_QUIT:
				std::cout << "ModelViewer was closed\n";
				framework->hasQuit = true;
				break;

			case SDL_MOUSEMOTION:
				if (framework -> isCursorLocked)
					camera->ChangeViewFromMouse(events.motion.xrel, events.motion.yrel);
				break;

			case SDL_KEYDOWN:
				switch (events.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					if (framework->isCursorLocked)
					{
						std::cout << "Left Inside-Mode\n";
						framework->LockCursor(false);
					}
					else
					{
						std::cout << "ModelViewer was closed\n";
						framework->hasQuit = true;
					}
					break;

				case SDLK_r:
					mesh.Rotate(3, glm::vec3(1, 1, 1));
					break;
				//Light on Arrow-keys
				case SDLK_UP:
					light->Translate(0, 0, -0.3);
					break;

				case SDLK_DOWN:
					light->Translate(0, 0, 0.3);
					break;

				case SDLK_LEFT:
					light->Translate(-0.3, 0, 0);
					break;

				case SDLK_RIGHT:
					light->Translate(0.3, 0, 0);
					break;
				//Camera on WASD
				case SDLK_w:
					camera->Translate(0, 0, -0.3);
					break;
				case SDLK_s:
					camera->Translate(0, 0, 0.3);
					break;
				case SDLK_a:
					camera->Translate(-0.3, 0, 0);
					break;
				case SDLK_d:
					camera->Translate(0.3, 0, 0);
					break;
				//ADDITIONALS like in Gameengine
				case SDLK_q:
					camera->Translate(0, -0.3, 0);
					break;

				case SDLK_e:
					camera->Translate(0, 0.3, 0);
					break;

				default:
					break;
				}
				break;

			case SDL_KEYUP:
				//system("cls");
				std::cout << "Light Position: " << light->position.x << " / " << light->position.y << " / " << light->position.z << '\n';
				std::cout << "Camera Position: " << camera->position.x << " / " << camera->position.y << " / " << camera->position.z << '\n';
				std::cout << "Object Rotation: " << mesh.GetRotation().x << " / " << mesh.GetRotation().y << " / " << mesh.GetRotation().z << '\n';
				break;
			
			case SDL_MOUSEBUTTONDOWN:
				if (events.button.button == SDL_BUTTON_LEFT && !framework->isCursorLocked)
					std::cout << "Went into Inside-Mode\n";
					framework->LockCursor(true);

			default:
				break;
			}
		}
		
	}


	// CLEAN UP //
	framework->Close();
	mesh.Release();
	delete framework;

    return 0;
}

