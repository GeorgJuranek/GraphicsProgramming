#pragma once
#include "GL\glew.h"
#include <string>

class Buffer
{
public:
	void CreateBufferObject();
	void SetAttributeId(std::string, GLuint);
	void Bind(GLenum);
	void Fill(GLsizeiptr, const void*, GLenum);
	void LinkAttribute(GLint, GLenum, GLboolean, GLsizei, const void*);
	void EnableAttribute();
	void Delete();

private:
	GLuint bufferObjectID;
	GLuint attributeID;
	GLenum target;
};

