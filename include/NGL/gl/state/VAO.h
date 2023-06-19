#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/gl/state/VBO.h"

NGL_BEGIN

namespace ngs_gl {
	template<Fundamental _T>
	GLenum Convert() { return 0; }

	template<>
	GLenum Convert<ngs::float32>() { return GL_FLOAT; }
	template<>
	GLenum Convert<ngs::float64>() { return GL_DOUBLE; }
	template<>
	GLenum Convert<ngs::int8>() { return GL_BYTE; }
	template<>
	GLenum Convert<ngs::int16>() { return GL_SHORT; }
	template<>
	GLenum Convert<ngs::int32>() { return GL_INT; }
	template<>
	GLenum Convert<ngs::uint8>() { return GL_UNSIGNED_BYTE; }
	template<>
	GLenum Convert<ngs::uint16>() { return GL_UNSIGNED_SHORT; }
	template<>
	GLenum Convert<ngs::uint32>() { return GL_UNSIGNED_INT; }
	template<>
	GLenum Convert<bool>() { return GL_BOOL; }

}

class VAO {
public:

public:
	VAO();
	~VAO()noexcept;

	void Bind()const noexcept;
	static void Unbind() noexcept;

	static void EnableAttribute(GLuint index)noexcept;
	static void DisableAttribute(GLuint index)noexcept;

	static void SetAttributePoint(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)noexcept;

	template<Arithmetic _Number, size_t _Count>
	static void SetAttributePoint(GLuint index, const VectorND<_Count, _Number>* data, GLsizei stride)noexcept {
		SetAttributePoint(index, _Count, ngs_gl::Convert<_Number>(), GL_FALSE, stride, data);
	}
private:

private:
	GLuint _id = 0;
	std::vector<VBO> _vbos;
};

NGL_END
