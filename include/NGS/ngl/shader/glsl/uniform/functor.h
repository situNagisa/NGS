#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/shader/glsl/uniform/location.h"

NGL_BEGIN
namespace map {

template<class _Type, size_t _Dimension = 1, size_t _Count = 1>
inline void* get_gl_set_uniform = nullptr;

template<> inline auto get_gl_set_uniform<GLfloat, 1, 1> = glUniform1f;
template<> inline auto get_gl_set_uniform<GLfloat, 2, 1> = glUniform2f;
template<> inline auto get_gl_set_uniform<GLfloat, 3, 1> = glUniform3f;
template<> inline auto get_gl_set_uniform<GLfloat, 4, 1> = glUniform4f;

template<> inline auto get_gl_set_uniform<GLdouble, 1, 1> = glUniform1d;
template<> inline auto get_gl_set_uniform<GLdouble, 2, 1> = glUniform2d;
template<> inline auto get_gl_set_uniform<GLdouble, 3, 1> = glUniform3d;
template<> inline auto get_gl_set_uniform<GLdouble, 4, 1> = glUniform4d;

template<> inline auto get_gl_set_uniform<GLint, 1, 1> = glUniform1i;
template<> inline auto get_gl_set_uniform<GLint, 2, 1> = glUniform2i;
template<> inline auto get_gl_set_uniform<GLint, 3, 1> = glUniform3i;
template<> inline auto get_gl_set_uniform<GLint, 4, 1> = glUniform4i;

template<> inline auto get_gl_set_uniform<GLuint, 1, 1> = glUniform1ui;
template<> inline auto get_gl_set_uniform<GLuint, 2, 1> = glUniform2ui;
template<> inline auto get_gl_set_uniform<GLuint, 3, 1> = glUniform3ui;
template<> inline auto get_gl_set_uniform<GLuint, 4, 1> = glUniform4ui;

template<size_t _Count> inline auto get_gl_set_uniform<GLfloat, 1, _Count> = glUniform1fv;
template<size_t _Count> inline auto get_gl_set_uniform<GLfloat, 2, _Count> = glUniform2fv;
template<size_t _Count> inline auto get_gl_set_uniform<GLfloat, 3, _Count> = glUniform3fv;
template<size_t _Count> inline auto get_gl_set_uniform<GLfloat, 4, _Count> = glUniform4fv;

template<size_t _Count> inline auto get_gl_set_uniform<GLint, 1, _Count> = glUniform1iv;
template<size_t _Count> inline auto get_gl_set_uniform<GLint, 2, _Count> = glUniform2iv;
template<size_t _Count> inline auto get_gl_set_uniform<GLint, 3, _Count> = glUniform3iv;
template<size_t _Count> inline auto get_gl_set_uniform<GLint, 4, _Count> = glUniform4iv;

template<size_t _Count> inline auto get_gl_set_uniform<GLuint, 1, _Count> = glUniform1uiv;
template<size_t _Count> inline auto get_gl_set_uniform<GLuint, 2, _Count> = glUniform2uiv;
template<size_t _Count> inline auto get_gl_set_uniform<GLuint, 3, _Count> = glUniform3uiv;
template<size_t _Count> inline auto get_gl_set_uniform<GLuint, 4, _Count> = glUniform4uiv;

template<class _Type, size_t _Row, size_t _Col>
inline void* get_gl_set_uniform_matrix = nullptr;

template<> inline auto get_gl_set_uniform_matrix<GLfloat, 2, 2> = glUniformMatrix2fv;
template<> inline auto get_gl_set_uniform_matrix<GLfloat, 2, 3> = glUniformMatrix2x3fv;
template<> inline auto get_gl_set_uniform_matrix<GLfloat, 2, 4> = glUniformMatrix2x4fv;
template<> inline auto get_gl_set_uniform_matrix<GLfloat, 3, 2> = glUniformMatrix3x2fv;
template<> inline auto get_gl_set_uniform_matrix<GLfloat, 3, 3> = glUniformMatrix3fv;
template<> inline auto get_gl_set_uniform_matrix<GLfloat, 3, 4> = glUniformMatrix3x4fv;
template<> inline auto get_gl_set_uniform_matrix<GLfloat, 4, 2> = glUniformMatrix4x2fv;
template<> inline auto get_gl_set_uniform_matrix<GLfloat, 4, 3> = glUniformMatrix4x3fv;
template<> inline auto get_gl_set_uniform_matrix<GLfloat, 4, 4> = glUniformMatrix4fv;

template<> inline auto get_gl_set_uniform_matrix<GLdouble, 2, 2> = glUniformMatrix2dv;
template<> inline auto get_gl_set_uniform_matrix<GLdouble, 2, 3> = glUniformMatrix2x3dv;
template<> inline auto get_gl_set_uniform_matrix<GLdouble, 2, 4> = glUniformMatrix2x4dv;
template<> inline auto get_gl_set_uniform_matrix<GLdouble, 3, 2> = glUniformMatrix3x2dv;
template<> inline auto get_gl_set_uniform_matrix<GLdouble, 3, 3> = glUniformMatrix3dv;
template<> inline auto get_gl_set_uniform_matrix<GLdouble, 3, 4> = glUniformMatrix3x4dv;
template<> inline auto get_gl_set_uniform_matrix<GLdouble, 4, 2> = glUniformMatrix4x2dv;
template<> inline auto get_gl_set_uniform_matrix<GLdouble, 4, 3> = glUniformMatrix4x3dv;
template<> inline auto get_gl_set_uniform_matrix<GLdouble, 4, 4> = glUniformMatrix4dv;

template<uint16 _Dimension>
constexpr Point2<uint8> convert_to_matrix_row_col{ (_Dimension >> (1 * bit::bit_per_byte)) & bit::mask(1 * bit::bit_per_byte),_Dimension & bit::mask(1 * bit::bit_per_byte) };
template<uint8 _Row, uint8 _Col>
constexpr uint16 convert_to_dimension = (_Row << (1 * bit::bit_per_byte)) | _Col;

template<class _Type, size_t _Dimension = 1, size_t _Count = 1>
inline void gl_set_uniform(uniform_offset_t location, const _Type* data) {
	if constexpr (_Dimension > bit::mask(1 * bit::bit_per_byte)) {
		constexpr auto row_col = convert_to_matrix_row_col<_Dimension>;
		get_gl_set_uniform_matrix<_Type, row_col.x, row_col.y>(location, _Count, GL_TRUE, data);
	}
	else {
		if constexpr (_Count == 1) {
			if constexpr (_Dimension == 1) {
				get_gl_set_uniform<_Type, 1, 1>(location, data[0]);
			}
			else if constexpr (_Dimension == 2) {
				get_gl_set_uniform<_Type, 2, 1>(location, data[0], data[1]);
			}
			else if constexpr (_Dimension == 3) {
				get_gl_set_uniform<_Type, 3, 1>(location, data[0], data[1], data[2]);
			}
			else if constexpr (_Dimension == 4) {
				get_gl_set_uniform<_Type, 4, 1>(location, data[0], data[1], data[2], data[3]);
			}
			else {

			}
		}
		else {
			get_gl_set_uniform<_Type, _Dimension, _Count>(location, _Count, data);
		}
	}
}

}
NGL_END
