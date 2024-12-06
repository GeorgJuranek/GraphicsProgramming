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
	mesh.Init(shader, material);

	////Texture
	//Texture* texture = new Texture();
	//texture->CreateTexture();
	//texture->SetImage("Textures/BricksTexture.png");//"C:\\Users\\Georg\\Desktop\\GraphicsProgramming\\GraphicsProgramming\\Textures\\BricksTexture.png");


	//The CAMERA
	Camera* camera = new Camera();
	camera->Init();


	//Infos to Console
    std::cout << "Graphics Programming Console:\n";
	std::cout << "Hold 'r' to rotate the object.\n";
	std::cout << "Use 'W'A'S'D' to move the light.\n";
	std::cout << "Use Arrow-keys to move the camera.\n";

	// LOOP //
	while (!framework->hasQuit)
	{

		// RENDERING //
		glClearColor(1, 0.33, 0.33, 1);

		glClear(GL_COLOR_BUFFER_BIT);

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

			case SDL_KEYDOWN:
				switch (events.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					std::cout << "ModelViewer was closed\n";
					framework->hasQuit = true;
					break;

				case SDLK_r:
					mesh.Rotate(3, glm::vec3(0, 1, 1));
					break;
				//WASD for light
				case SDLK_w:
					light->Translate(0, 0, -0.3);
					break;

				case SDLK_s:
					light->Translate(0, 0, 0.3);
					break;

				case SDLK_a:
					light->Translate(-0.3, 0, 0);
					break;

				case SDLK_d:
					light->Translate(0.3, 0, 0);
					break;
				//Camera on arrowkeys
				case SDLK_UP:
					camera->Translate(0, 0, -0.3);
					break;
				case SDLK_DOWN:
					camera->Translate(0, 0, 0.3);
					break;
				case SDLK_LEFT:
					camera->Translate(-0.3, 0, 0);
					break;
				case SDLK_RIGHT:
					camera->Translate(0.3, 0, 0);
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
