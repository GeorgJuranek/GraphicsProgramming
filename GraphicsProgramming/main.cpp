#include <iostream>

#include "Framework.h"
#include "Shader.h"
#include "Light.h"
#include "Material.h"
#include "Mesh.h"

int main(int argc, char* argv[])
{
    std::cout << "Graphics Programming Console:\n";

	Framework* framework = new Framework();
    framework->Init();

	Shader* shader = new Shader();
	shader->Init("BasicColorLit.vert", "BasicColorLit.frag"); //("Shader/BasicColorLit.vert", "Shader/BasicColorLit.frag"); //("BasicColorLit", "Shader"); //???


	/* //LESSON 2

	//TRIANGLE DUMMY//
	GLfloat triangleData[] = {
		//	  X	   Y	Z		  R		G	 B    
			-0.5, -0.5, 0.0f,	1.0f, 0.0f, 0.0f, //Vertex1
			0.0f, 0.5,  0.0f,	0.0f, 1.0f, 0.0f, //Vertex2
			0.5,  -0.5, 0.0f,	0.0f, 0.0f, 1.0f, //Vertex2
	};////////////////
	
	GLuint indices[] = { 0, 1, 2 };
	*/

	/* // Shader //
	Shader basicShader;
	basicShader.Init("Shader\\Basic.vert", "Shader\\Basic.frag");

	// SHADER SETUP
	GLint vertexAttribID = glGetAttribLocation(basicShader.programID, "vertexIn");
	if (vertexAttribID == -1)
		std::cerr << "Error in vertexIn of Shader" << "\n";

	GLint colorAttribID = glGetAttribLocation(basicShader.programID, "colorIn");
	if (colorAttribID == -1)
		std::cerr << "Error in colorIn of Shader" << "\n";
	*/

	/* ///BUFFER///
	//3) VERTEX ARRAY OBJECT//
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//1) VERTEX BUFFER OBJECT// -> ALL Vertex Data
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

	//2) ELEMENT BUFFER OBJECT// -> Indices (Better Order and Structure of Vertex data)
	GLuint elementBufferObject;
	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//CONNECT SHADER AND BUFFER//
	glVertexAttribPointer(vertexAttribID, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glVertexAttribPointer(colorAttribID, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); //?wtf is GLvoidPointer?

	//ENABLE USE OF POISITION AND COLOR INFORMATION FOR CURRENT SHADER
	glEnableVertexAttribArray(vertexAttribID);
	glEnableVertexAttribArray(colorAttribID);

	//VAO UNBIND
	glBindVertexArray(0);

	*/

	//LIGHT//
	//Blinn-Phong-Shading (per vertex)
	Light* light = new Light();
	light->Init();

	Material* material = new Material();

	Mesh mesh;
	mesh.Init(shader, material);

	/*Camera* camera = new Camera();
	camera->Init();*/

	// LOOP //
	while (!framework->hasQuit)// && framework->context != nullptr) // -> BUG: Why not !framework.hasQuit ???
	{
		framework->CheckForClosingEvents();

		// RENDERING //
		glClearColor(1, 0.33, 0.33, 1);
		glClear(GL_COLOR_BUFFER_BIT);



		//glBindVertexArray(vertexArrayObject);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		mesh.Draw(light);//, camera);


		if (framework->window != nullptr)
			framework->SwapWindow();
		else
			std::cerr << "framework window is missing";
	}


	// CLEAN UP //
	framework->Close();
	//glDeleteVertexArrays(1, &vertexArrayObject);
	mesh.Release();
	delete framework;

    return 0;
}
