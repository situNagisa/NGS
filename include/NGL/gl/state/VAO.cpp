#include "NGL/gl/state/VAO.h"

NGL_BEGIN

VAO::VAO()
{
	glGenVertexArrays(1, &_id);
}
VAO::~VAO() noexcept
{
	glDeleteVertexArrays(1, &_id);
	_id = 0;
}

void VAO::Bind() const noexcept
{
	glBindVertexArray(_id);
}
void VAO::Unbind() noexcept
{
	glBindVertexArray(0);
}

void VAO::EnableAttribute(GLuint index) noexcept
{
	glEnableVertexAttribArray(index);
}

void VAO::DisableAttribute(GLuint index) noexcept
{
	glDisableVertexAttribArray(index);
}

void VAO::SetAttributePoint(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) noexcept
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}




NGL_END


