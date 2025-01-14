#include "Buffer.h"
#include <iostream>
#include "GL\glew.h"

void Buffer::CreateBufferObject()
{
	glGenBuffers(1, &bufferObjectID);
}

void Buffer::SetAttributeId( GLuint id)
{
	attributeID = id;
	if (attributeID == -1)
	{
		std::cerr << "Shader or Shader attribute does not exist" << '\n';
	}
}

void Buffer::Bind(GLenum target)
{
	this->target = target;
	glBindBuffer(this->target, bufferObjectID);
}

void Buffer::Fill(GLsizeiptr size, const void* data, GLenum usage)
{
	glBufferData(this->target, size, data, usage);
}

// size = wie viele floats
// stride = wie viele Bytes ist mein Vertex groﬂ
// pointer = wie viele bytes von der startadresse des vertex muss ich nach vorne springen um Position/Color/TexCoord etc zu erreichen
void Buffer::LinkAttribute(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	glVertexAttribPointer(attributeID, size, type, normalized, stride, pointer);
}

void Buffer::EnableAttribute()
{
	glEnableVertexAttribArray(attributeID);
}

void Buffer::Delete()
{
	glDeleteBuffers(1, &bufferObjectID);
}
