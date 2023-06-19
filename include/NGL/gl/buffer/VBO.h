#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"

NGL_BEGIN

class VBO {
public:

public:
	VBO();
	~VBO()noexcept;

	void Bind()const noexcept;
	static void Unbind() noexcept;

	static void SetData(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW) noexcept;

private:

private:
	GLuint _id = 0;
};

NGL_END
