#include "NGL/gl/buffer/VBO.h"

NGL_BEGIN

VBO::VBO()
{
	glGenBuffers(1, &_id);
}
VBO::~VBO() noexcept
{
	glDeleteBuffers(1, &_id);
	_id = 0;
}

void VBO::Bind() const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}
void VBO::Unbind() noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::SetData(const void* data, size_t size, GLenum usage) noexcept
{
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}



NGL_END


