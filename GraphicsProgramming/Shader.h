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
	const GLuint& programID = ShaderProgramID;

	void Init(std::string, std::string = "");
	void Release();
	GLuint GetAttributeLocation(const GLchar*);
	GLuint GetUniformLocation(const GLchar*);

private:
	std::string vertexName, fragmentName;

	GLuint ShaderProgramID;
	GLuint vertexShaderID, fragmentShaderID;

	void CreateShaderProgram();
	void CreateShaderObjects();
	void CompileShader(GLuint, std::string);
	void CompileShaders();
	void AttackShaders();
	void LinkShaderProgram();

	void DetachShader();


};