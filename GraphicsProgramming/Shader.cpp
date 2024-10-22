#pragma once

#include "Shader.h"
#include <iostream>

void Shader::CreateShaderProgram()
{
	ShaderProgramID = glCreateProgram();

	if (ShaderProgramID == 0)
	{
		std::cerr << "Shader not working";
	}
}
