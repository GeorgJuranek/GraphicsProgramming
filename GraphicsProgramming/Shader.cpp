#pragma once

#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>

void Shader::Init(std::string vertex, std::string fragment)
{
	shaderProgramID = 0;
	vertexShaderID = 0;
	fragmentShaderID = 0;

	vertexName = vertex;
	fragmentName = fragment;

	//Version2: ShaderName//ordner // OCE30OCT24
	/*
	vertexName = folderPath+\\"+ name + ".vert;
	fragmentName = folderPath+\\"+ name + ".frag; 
	*/

	CreateShaderProgram();
	CreateShaderObjects();
	CompileShaders();
	AttachShaders();
	LinkShaderProgram();
}

void Shader::Release()
{
	DetachShader();
}

GLuint Shader::GetAttributeLocation(const GLchar*)
{
	return GLuint();
}

GLuint Shader::GetUniformLocation(const GLchar*)
{
	return GLuint();
}

void Shader::CreateShaderProgram()
{
	shaderProgramID = glCreateProgram();

	if (shaderProgramID == 0) //special case "0" means not working
	{
		std::cerr << "Shader not working";
	}
}

void Shader::CreateShaderObjects()
{
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0)
		std::cerr << "Failed VertexShader\n";

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0)
		std::cerr << "Failed FragmentShader\n";
}

void Shader::CompileShader(GLuint shaderID, std::string fileName)
{
	GLint compileResult;
	const GLchar* finalCode;

	std::string content = ReadFile(fileName);
	finalCode = (const GLchar*)(content.c_str());
	glShaderSource(shaderID, 1, &finalCode, nullptr);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult); //Debug
	if (compileResult == GL_FALSE)
	{
		std::cerr << "Could not create shader for " << fileName << "\n";

		GLchar error[1000];
		GLsizei length = 1000;

		glGetShaderInfoLog(shaderID, 1000, &length, error);
		std::cerr << error << '\n';
	}

}

void Shader::CompileShaders(void)
{
	CompileShader(vertexShaderID, vertexName);
	CompileShader(fragmentShaderID, fragmentName);
}

void Shader::AttachShaders()
{
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
}

void Shader::LinkShaderProgram()
{
	GLint linkResult;

	glLinkProgram(shaderProgramID);

	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_FALSE)
	{
		GLchar error[1000];
		GLsizei length = 1000;

		glGetShaderInfoLog(shaderProgramID, 1000, &length, error);
		std::cerr << "Shaderprogram did not link" << error << '\n';
	}
	else
	{
		glUseProgram(shaderProgramID); //Solution if only ONE shader, must be done at other place for more than one shader
	}
}


//Destruction
void Shader::DetachShader()
{
	glDetachShader(shaderProgramID, vertexShaderID);
	glDetachShader(shaderProgramID, fragmentShaderID);
}

void Shader::DestroyShaders()
{
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::DestroyProgram()
{
	glDeleteProgram(shaderProgramID);
}

//Helper
std::string Shader::ReadFile(std::string fileName)
{
	std::fstream file;
	std::string lineText = "";
	std::string finalString = "";

	file.open(fileName);

	if (!file)
	{
		std::cerr << "Shader file could not be opened" << "\n";
	}

	while (!file.eof())
	{
		getline(file, lineText);
		finalString += lineText + '\n';
	}

	file.close();

	return finalString;
}
