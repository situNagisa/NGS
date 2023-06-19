#include "NGL/gl/buffer/EBO.h"

NGL_BEGIN

EBO::EBO()
{
	glGenBuffers(1, &_id);
}
EBO::~EBO() {
	glDeleteBuffers(1, &_id);
}

EBO::__context EBO::GetContext() { return __context(); }


void EBO::Bind() const noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void EBO::Unbind() noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::SetData(const void* data, size_t size, GLenum usage) noexcept
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}



NGL_END

