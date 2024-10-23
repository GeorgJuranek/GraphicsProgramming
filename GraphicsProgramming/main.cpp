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




	// Shader //
	Shader basicShader;
	basicShader.Init("src\\Basic.vert", "src\\Basi.frag");
	// SETUP
	GLuint vertexAttribID = glGetAttribLocation(basicShader.programID, "vertexIn");
	if (vertexAttribID == -1)
		std::cerr << "Error in vertexIn of Shader";

	GLuint colorAttribID = glGetAttribLocation(basicShader.programID, "colorIn");
	if (colorAttribID == -1)
		std::cerr << "Error in colorIn of Shader";

	glEnableVertexAttribArray(vertexAttribID);
	glEnableVertexAttribArray(colorAttribID);



	//VERTEX BUFFER OBJECT//
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

	glVertexAttribPointer(vertexAttribID, 3, GL_FLOAT, GL_FLOAT, 6 * sizeof(GLfloat), 0);
	glVertexAttribPointer(colorAttribID, 3, GL_FLOAT, GL_FLOAT, 6 * sizeof(GLfloat), (GLvoid*));



	// LOOP //
	while (!framework.hasQuit)
	{
		framework.CheckForClosingEvents();



		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}



    return 0;
}
