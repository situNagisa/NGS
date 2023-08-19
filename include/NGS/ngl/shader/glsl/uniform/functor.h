#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/shader/glsl/uniform/location.h"

NGL_BEGIN
namespace map {

template<class _Type, size_t _Dimension = 1, size_t _Count = 1>
struct get_gl_set_uniform { inline static void* value = nullptr; };

template<> struct get_gl_set_uniform<GLfloat, 1, 1> { inline static auto& value = glUniform1f;};
template<> struct get_gl_set_uniform<GLfloat, 2, 1> { inline static auto& value = glUniform2f;};
template<> struct get_gl_set_uniform<GLfloat, 3, 1> { inline static auto& value = glUniform3f;};
template<> struct get_gl_set_uniform<GLfloat, 4, 1> { inline static auto& value = glUniform4f;};
template<> struct get_gl_set_uniform<GLdouble, 1, 1> { inline static auto& value = glUniform1d;};
template<> struct get_gl_set_uniform<GLdouble, 2, 1> { inline static auto& value = glUniform2d;};
template<> struct get_gl_set_uniform<GLdouble, 3, 1> { inline static auto& value = glUniform3d;};
template<> struct get_gl_set_uniform<GLdouble, 4, 1> { inline static auto& value = glUniform4d;};
template<> struct get_gl_set_uniform<GLint, 1, 1> { inline static auto& value = glUniform1i;};
template<> struct get_gl_set_uniform<GLint, 2, 1> { inline static auto& value = glUniform2i;};
template<> struct get_gl_set_uniform<GLint, 3, 1> { inline static auto& value = glUniform3i;};
template<> struct get_gl_set_uniform<GLint, 4, 1> { inline static auto& value = glUniform4i;};
template<> struct get_gl_set_uniform<GLuint, 1, 1> { inline static auto& value = glUniform1ui;};
template<> struct get_gl_set_uniform<GLuint, 2, 1> { inline static auto& value = glUniform2ui;};
template<> struct get_gl_set_uniform<GLuint, 3, 1> { inline static auto& value = glUniform3ui;};
template<> struct get_gl_set_uniform<GLuint, 4, 1> { inline static auto& value = glUniform4ui;};

template<size_t _Count> struct get_gl_set_uniform<GLfloat, 1, _Count> { inline static auto& value = glUniform1fv;};
template<size_t _Count> struct get_gl_set_uniform<GLfloat, 2, _Count>{ inline static auto& value = glUniform2fv;};
template<size_t _Count> struct get_gl_set_uniform<GLfloat, 3, _Count>{ inline static auto& value = glUniform3fv;};
template<size_t _Count> struct get_gl_set_uniform<GLfloat, 4, _Count>{ inline static auto& value = glUniform4fv;};
template<size_t _Count> struct get_gl_set_uniform<GLint, 1, _Count>{ inline static auto& value = glUniform1iv;};
template<size_t _Count> struct get_gl_set_uniform<GLint, 2, _Count>{ inline static auto& value = glUniform2iv;};
template<size_t _Count> struct get_gl_set_uniform<GLint, 3, _Count>{ inline static auto& value = glUniform3iv;};
template<size_t _Count> struct get_gl_set_uniform<GLint, 4, _Count>{ inline static auto& value = glUniform4iv;};
template<size_t _Count> struct get_gl_set_uniform<GLuint, 1, _Count>{ inline static auto& value = glUniform1uiv;};
template<size_t _Count> struct get_gl_set_uniform<GLuint, 2, _Count>{ inline static auto& value = glUniform2uiv;};
template<size_t _Count> struct get_gl_set_uniform<GLuint, 3, _Count>{ inline static auto& value = glUniform3uiv;};
template<size_t _Count> struct get_gl_set_uniform<GLuint, 4, _Count> { inline static auto& value = glUniform4uiv; };

template<class _Type, uint8 _Row, uint8 _Col>
struct get_gl_set_uniform_matrix { inline static void* value = nullptr; };

template<> struct get_gl_set_uniform_matrix<GLfloat, 2, 2> { inline static auto& value = glUniformMatrix2fv;};
template<> struct get_gl_set_uniform_matrix<GLfloat, 2, 3> { inline static auto& value = glUniformMatrix2x3fv;};
template<> struct get_gl_set_uniform_matrix<GLfloat, 2, 4> { inline static auto& value = glUniformMatrix2x4fv;};
template<> struct get_gl_set_uniform_matrix<GLfloat, 3, 2> { inline static auto& value = glUniformMatrix3x2fv;};
template<> struct get_gl_set_uniform_matrix<GLfloat, 3, 3> { inline static auto& value = glUniformMatrix3fv;};
template<> struct get_gl_set_uniform_matrix<GLfloat, 3, 4> { inline static auto& value = glUniformMatrix3x4fv;};
template<> struct get_gl_set_uniform_matrix<GLfloat, 4, 2> { inline static auto& value = glUniformMatrix4x2fv;};
template<> struct get_gl_set_uniform_matrix<GLfloat, 4, 3> { inline static auto& value = glUniformMatrix4x3fv;};
template<> struct get_gl_set_uniform_matrix<GLfloat, 4, 4> { inline static auto& value = glUniformMatrix4fv;};
template<> struct get_gl_set_uniform_matrix<GLdouble, 2, 2> { inline static auto& value = glUniformMatrix2dv;};
template<> struct get_gl_set_uniform_matrix<GLdouble, 2, 3> { inline static auto& value = glUniformMatrix2x3dv;};
template<> struct get_gl_set_uniform_matrix<GLdouble, 2, 4> { inline static auto& value = glUniformMatrix2x4dv;};
template<> struct get_gl_set_uniform_matrix<GLdouble, 3, 2> { inline static auto& value = glUniformMatrix3x2dv;};
template<> struct get_gl_set_uniform_matrix<GLdouble, 3, 3> { inline static auto& value = glUniformMatrix3dv;};
template<> struct get_gl_set_uniform_matrix<GLdouble, 3, 4> { inline static auto& value = glUniformMatrix3x4dv;};
template<> struct get_gl_set_uniform_matrix<GLdouble, 4, 2> { inline static auto& value = glUniformMatrix4x2dv;};
template<> struct get_gl_set_uniform_matrix<GLdouble, 4, 3> { inline static auto& value = glUniformMatrix4x3dv;};
template<> struct get_gl_set_uniform_matrix<GLdouble, 4, 4> { inline static auto& value = glUniformMatrix4dv; };

template<uint16 _Dimension>
constexpr Point2<uint8> convert_to_matrix_row_col{ (_Dimension >> (1 * bit::bit_per_byte)) & bit::mask(1 * bit::bit_per_byte),_Dimension & bit::mask(1 * bit::bit_per_byte) };
template<uint8 _Row, uint8 _Col>
constexpr uint16 convert_to_dimension = (_Row << (1 * bit::bit_per_byte)) | _Col;
template<uint16 _Dimension>
constexpr bool is_matrix_dimension = (_Dimension >> (1 * bit::bit_per_byte));
template<uint16 _Dimension>
constexpr bool is_vector_dimension = !is_matrix_dimension<_Dimension>;

template<class _Type, size_t _Dimension = 1, size_t _Count = 1>
inline void gl_set_uniform(uniform_offset_t location, const _Type* data) {
	if constexpr (_Dimension > bit::mask(1 * bit::bit_per_byte)) {
		constexpr auto row_col = convert_to_matrix_row_col<_Dimension>;
		get_gl_set_uniform_matrix<_Type, row_col.x, row_col.y>::value(location, _Count, GL_TRUE, data);
	}
	else {
		if constexpr (_Count == 1) {
			if constexpr (_Dimension == 1) {
				get_gl_set_uniform<_Type, 1, 1>::value(location, data[0]);
			}
			else if constexpr (_Dimension == 2) {
				get_gl_set_uniform<_Type, 2, 1>::value(location, data[0], data[1]);
			}
			else if constexpr (_Dimension == 3) {
				get_gl_set_uniform<_Type, 3, 1>::value(location, data[0], data[1], data[2]);
			}
			else if constexpr (_Dimension == 4) {
				get_gl_set_uniform<_Type, 4, 1>::value(location, data[0], data[1], data[2], data[3]);
			}
			else {

			}
		}
		else {
			get_gl_set_uniform<_Type, _Dimension, _Count>::value(location, _Count, data);
		}
	}
}

}
NGL_END
