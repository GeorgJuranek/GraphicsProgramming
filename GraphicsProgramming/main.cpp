#include <iostream>

#include "Framework.h"
#include "Shader.h"
#include "Light.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"

int main(int argc, char* argv[])
{
    std::cout << "Graphics Programming Console:\n";


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


	//The CAMERA
	Camera* camera = new Camera();
	camera->Init();


	//The Texture
	//Texture* texture = new Texture();
	//texture->CreateTexture();
	//texture->SetImage();


	/*SHADER PROGRAMMING lesson2
	//framework->SetClearColor(0,0,0,1);
	//framework->SetFrontfaceDirection(GL_CCW); //GL_CounterClockWise// ,GL_CW);
	//framework->EnableFaceCulling(GL_BACK); // ,GL_FRONT);
	//framework->EnableDepthTest();
	*/

	//Infos to Console//
	std::cout << "Hold 'r' to rotate the object.\n";
	std::cout << "Use 'W'A'S'D' to move the light.\n";

	// LOOP //
	while (!framework->hasQuit)
	{
		//framework->CheckForClosingEvents();

		// RENDERING //
		glClearColor(1, 0.33, 0.33, 1);
		//glClearColor(0, 0, 0, 0);

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

		/*SDL_Keycode currentKey = Framework::GetCurrentKeyCode();

		if (currentKey == SDL_KeyCode::SDLK_r)
		{
			mesh.Rotate(3,glm::vec3(0,1,1));
			std::cout << "rotated\n";
		}

		if (currentKey == SDL_KeyCode::SDLK_w)
		{
			light->Translate(0, 0, -0.3);
			std::cout << "translated\n" << light->position.x << " " << light->position.y << " " << light->position.z << " " << "\n";
		}
		
		if (currentKey == SDL_KeyCode::SDLK_s)
		{
			light->Translate(0, 0, 0.3);
			std::cout << "translated\n" << light->position.x << " " << light->position.y << " " << light->position.z << " " << "\n";
		}

		if (currentKey == SDL_KeyCode::SDLK_a)
		{
			light->Translate(-0.3, 0, 0);
			std::cout << "translated\n" << light->position.x << " " << light->position.y << " " << light->position.z << " " << "\n";
		}

		if (currentKey == SDL_KeyCode::SDLK_d)
		{
			light->Translate(0.3, 0, 0);
			std::cout << "translated\n" << light->position.x << " " << light->position.y << " " << light->position.z << " " << "\n";
		}

		//
		if (currentKey == SDL_QUIT)
		{
			std::cout << "ModelViewer was closed";
			framework->hasQuit = true;
		}

		if (currentKey == SDL_KEYDOWN)
		{
			SDL_Event events;
			while (SDL_PollEvent(&events))
			{
				if (events.key.keysym.sym == SDLK_ESCAPE) //-> ESC
				{
					std::cout << "ModelViewer was closed";
					framework->hasQuit = true;
				}
			}
		}*/

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
		

		//std::cout << framework->GetCurrentKeyCode();
	}


	// CLEAN UP //
	framework->Close();
	mesh.Release();
	delete framework;

    return 0;
}
