#include <iostream>

#include "Framework.h"
#include "Shader.h"

int main(int argc, char* argv[])
{
    std::cout << "Graphics Programming Console:\n";

    Framework framework;

    framework.Init();



    /*LESSON 2*/

	//TRIANGLE DUMMY//
	GLfloat triangleData[] = {
		/*	  X	   Y	Z		  R		G	 B    */
			-0.5, -0.5, 0.0f,	1.0f, 0.0f, 0.0f, //Vertex1
			0.0f, 0.5,  0.0f,	0.0f, 1.0f, 0.0f, //Vertex2
			0.5,  -0.5, 0.0f,	0.0f, 0.0f, 1.0f, //Vertex2
	};////////////////
	
	GLuint indices[] = { 0, 1, 2 };



	// Shader //
	Shader basicShader;
	basicShader.Init("Shader\\Basic.vert", "Shader\\Basic.frag");

	// SHADER SETUP
	GLint vertexAttribID = glGetAttribLocation(basicShader.programID, "vertexIn");
	if (vertexAttribID == -1)
		std::cerr << "Error in vertexIn of Shader" << "\n";

	GLint colorAttribID = glGetAttribLocation(basicShader.programID, "colorIn");
	if (colorAttribID == -1)
		std::cerr << "Error in colorIn of Shader" << "\n";

	

	//1) VERTEX BUFFER OBJECT// -> ALL Vertex Data
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);


	//CONNECT SHADER AND BUFFER//
	glVertexAttribPointer(vertexAttribID, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glVertexAttribPointer(colorAttribID, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); //?wtf is GLvoidPointer?


	//2) ELEMENT BUFFER OBJECT// -> Indices (Better Order and Structure of Vertex data)
	GLuint elementBufferObject;
	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//3) VERTEX ARRAY OBJECT//
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);


	//ENABLE USE OF POISITION AND COLOR INFORMATION FOR CURRENT SHADER
	glEnableVertexAttribArray(vertexAttribID);
	glEnableVertexAttribArray(colorAttribID);


	//LIGHT//
	//Blinn-Phong-Shading (per vertex)


	//VAO UNBIND
	glBindVertexArray(0);


	// LOOP //
	while (framework.hasQuit) // -> BUG: Why not !framework.hasQuit ???
	{
		framework.CheckForClosingEvents();

		// RENDERING //
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vertexArrayObject);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		framework.SwapWindow();
	}

	// CLEAN UP //
	framework.Close();
	glDeleteVertexArrays(1, &vertexArrayObject);

    return 0;
}
