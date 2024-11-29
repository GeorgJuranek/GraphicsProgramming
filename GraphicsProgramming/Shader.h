#pragma once

#include <iostream>
#include "GL\glew.h"

class Shader
{
public:
	Shader() = default;
	Shader(const Shader&) = default;
	Shader& operator=(const Shader&) = default;

	//const GLuint& programID = shaderProgramID;
	const GLuint& programID = shaderProgramID;

	void Init(std::string, std::string = "");
	void Release();
	GLuint GetAttributeLocation(const GLchar*);
	GLuint GetUniformLocation(const GLchar*);

private:
	std::string vertexName, fragmentName;

	GLuint shaderProgramID;
	GLuint vertexShaderID, fragmentShaderID;

	void CreateShaderProgram();
	void CreateShaderObjects();
	void CompileShader(GLuint, std::string);
	void CompileShaders();
	void AttachShaders();
	void LinkShaderProgram();

	void DetachShader();
	void DestroyShaders();
	void DestroyProgram();

	std::string ReadFile(std::string);
};