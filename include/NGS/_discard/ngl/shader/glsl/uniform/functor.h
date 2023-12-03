#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/config.h"
#include "NGS/ngl/shader/glsl/uniform/location.h"

NGL_BEGIN
namespace map {

template<class _Type, size_t _Dimension = 1, size_t _Count = 1>
struct get_gl_set_uniform { inline static void* value = nullptr; };

template<> struct get_gl_set_uniform<GLfloat, 1, 1> { inline static auto& value = glUniform1f; };
template<> struct get_gl_set_uniform<GLfloat, 2, 1> { inline static auto& value = glUniform2f; };
template<> struct get_gl_set_uniform<GLfloat, 3, 1> { inline static auto& value = glUniform3f; };
template<> struct get_gl_set_uniform<GLfloat, 4, 1> { inline static auto& value = glUniform4f; };
template<> struct get_gl_set_uniform<GLdouble, 1, 1> { inline static auto& value = glUniform1d; };
template<> struct get_gl_set_uniform<GLdouble, 2, 1> { inline static auto& value = glUniform2d; };
template<> struct get_gl_set_uniform<GLdouble, 3, 1> { inline static auto& value = glUniform3d; };
template<> struct get_gl_set_uniform<GLdouble, 4, 1> { inline static auto& value = glUniform4d; };
template<> struct get_gl_set_uniform<GLint, 1, 1> { inline static auto& value = glUniform1i; };
template<> struct get_gl_set_uniform<GLint, 2, 1> { inline static auto& value = glUniform2i; };
template<> struct get_gl_set_uniform<GLint, 3, 1> { inline static auto& value = glUniform3i; };
template<> struct get_gl_set_uniform<GLint, 4, 1> { inline static auto& value = glUniform4i; };
template<> struct get_gl_set_uniform<GLuint, 1, 1> { inline static auto& value = glUniform1ui; };
template<> struct get_gl_set_uniform<GLuint, 2, 1> { inline static auto& value = glUniform2ui; };
template<> struct get_gl_set_uniform<GLuint, 3, 1> { inline static auto& value = glUniform3ui; };
template<> struct get_gl_set_uniform<GLuint, 4, 1> { inline static auto& value = glUniform4ui; };

template<size_t _Count> struct get_gl_set_uniform<GLfloat, 1, _Count> { inline static auto& value = glUniform1fv; };
template<size_t _Count> struct get_gl_set_uniform<GLfloat, 2, _Count> { inline static auto& value = glUniform2fv; };
template<size_t _Count> struct get_gl_set_uniform<GLfloat, 3, _Count> { inline static auto& value = glUniform3fv; };
template<size_t _Count> struct get_gl_set_uniform<GLfloat, 4, _Count> { inline static auto& value = glUniform4fv; };
template<size_t _Count> struct get_gl_set_uniform<GLint, 1, _Count> { inline static auto& value = glUniform1iv; };
template<size_t _Count> struct get_gl_set_uniform<GLint, 2, _Count> { inline static auto& value = glUniform2iv; };
template<size_t _Count> struct get_gl_set_uniform<GLint, 3, _Count> { inline static auto& value = glUniform3iv; };
template<size_t _Count> struct get_gl_set_uniform<GLint, 4, _Count> { inline static auto& value = glUniform4iv; };
template<size_t _Count> struct get_gl_set_uniform<GLuint, 1, _Count> { inline static auto& value = glUniform1uiv; };
template<size_t _Count> struct get_gl_set_uniform<GLuint, 2, _Count> { inline static auto& value = glUniform2uiv; };
template<size_t _Count> struct get_gl_set_uniform<GLuint, 3, _Count> { inline static auto& value = glUniform3uiv; };
template<size_t _Count> struct get_gl_set_uniform<GLuint, 4, _Count> { inline static auto& value = glUniform4uiv; };

template<class _Type, uint8 _Row, uint8 _Col>
struct get_gl_set_uniform_matrix { inline static void* value = nullptr; };

template<> struct get_gl_set_uniform_matrix<GLfloat, 2, 2> { inline static auto& value = glUniformMatrix2fv; };
template<> struct get_gl_set_uniform_matrix<GLfloat, 2, 3> { inline static auto& value = glUniformMatrix2x3fv; };
template<> struct get_gl_set_uniform_matrix<GLfloat, 2, 4> { inline static auto& value = glUniformMatrix2x4fv; };
template<> struct get_gl_set_uniform_matrix<GLfloat, 3, 2> { inline static auto& value = glUniformMatrix3x2fv; };
template<> struct get_gl_set_uniform_matrix<GLfloat, 3, 3> { inline static auto& value = glUniformMatrix3fv; };
template<> struct get_gl_set_uniform_matrix<GLfloat, 3, 4> { inline static auto& value = glUniformMatrix3x4fv; };
template<> struct get_gl_set_uniform_matrix<GLfloat, 4, 2> { inline static auto& value = glUniformMatrix4x2fv; };
template<> struct get_gl_set_uniform_matrix<GLfloat, 4, 3> { inline static auto& value = glUniformMatrix4x3fv; };
template<> struct get_gl_set_uniform_matrix<GLfloat, 4, 4> { inline static auto& value = glUniformMatrix4fv; };
template<> struct get_gl_set_uniform_matrix<GLdouble, 2, 2> { inline static auto& value = glUniformMatrix2dv; };
template<> struct get_gl_set_uniform_matrix<GLdouble, 2, 3> { inline static auto& value = glUniformMatrix2x3dv; };
template<> struct get_gl_set_uniform_matrix<GLdouble, 2, 4> { inline static auto& value = glUniformMatrix2x4dv; };
template<> struct get_gl_set_uniform_matrix<GLdouble, 3, 2> { inline static auto& value = glUniformMatrix3x2dv; };
template<> struct get_gl_set_uniform_matrix<GLdouble, 3, 3> { inline static auto& value = glUniformMatrix3dv; };
template<> struct get_gl_set_uniform_matrix<GLdouble, 3, 4> { inline static auto& value = glUniformMatrix3x4dv; };
template<> struct get_gl_set_uniform_matrix<GLdouble, 4, 2> { inline static auto& value = glUniformMatrix4x2dv; };
template<> struct get_gl_set_uniform_matrix<GLdouble, 4, 3> { inline static auto& value = glUniformMatrix4x3dv; };
template<> struct get_gl_set_uniform_matrix<GLdouble, 4, 4> { inline static auto& value = glUniformMatrix4dv; };

template<uint16 _Dimension>
constexpr Point2<uint8> convert_to_matrix_row_col{ (_Dimension >> (1 * bit::bit_per_byte)) & bit::mask(1 * bit::bit_per_byte),_Dimension & bit::mask(1 * bit::bit_per_byte) };
template<uint8 _Row, uint8 _Col>
constexpr uint16 convert_to_dimension = (_Row << (1 * bit::bit_per_byte)) | _Col;
template<uint16 _Dimension>
constexpr bool is_matrix_dimension = static_cast<bool>(_Dimension >> (1 * bit::bit_per_byte));
template<uint16 _Dimension>
constexpr bool is_vector_dimension = !is_matrix_dimension<_Dimension>;

constexpr auto matrix2x2 = convert_to_dimension<2, 2>;
constexpr auto matrix2x3 = convert_to_dimension<2, 3>;
constexpr auto matrix2x4 = convert_to_dimension<2, 4>;
constexpr auto matrix3x2 = convert_to_dimension<3, 2>;
constexpr auto matrix3x3 = convert_to_dimension<3, 3>;
constexpr auto matrix3x4 = convert_to_dimension<3, 4>;
constexpr auto matrix4x2 = convert_to_dimension<4, 2>;
constexpr auto matrix4x3 = convert_to_dimension<4, 3>;
constexpr auto matrix4x4 = convert_to_dimension<4, 4>;

template<class _Type, size_t _Count = 1>
void gl_set_uniform(uniform_offset_t location, void_ptr_cst data) {
	if constexpr (mla::CStandardMatrix<_Type>) {
		auto gl_uniform = get_gl_set_uniform_matrix<typename _Type::element_type, _Type::row_count, _Type::col_count>::value;
		auto data_temp = static_cast<const typename _Type::element_type*>(data);
		gl_uniform(location, _Count, NGL_UNIFORM_MATRIX_TRANSPOSE, data_temp);
	}
	else if constexpr (mla::CStandardVector<_Type>) {
		auto data_temp = static_cast<const typename _Type::element_type*>(data);
		if constexpr (_Count > 1) {
			get_gl_set_uniform<typename _Type::element_type, _Type::dimension, _Count>::value(location, _Count, data_temp);
		}
		else if constexpr (_Count == 1) {
			if constexpr (_Type::dimension == 1) {
				get_gl_set_uniform<typename _Type::element_type, 1, 1>::value(location, data_temp[0]);
			}
			else if constexpr (_Type::dimension == 2) {
				get_gl_set_uniform<typename _Type::element_type, 2, 1>::value(location, data_temp[0], data_temp[1]);
			}
			else if constexpr (_Type::dimension == 3) {
				get_gl_set_uniform<typename _Type::element_type, 3, 1>::value(location, data_temp[0], data_temp[1], data_temp[2]);
			}
			else if constexpr (_Type::dimension == 4) {
				get_gl_set_uniform<typename _Type::element_type, 4, 1>::value(location, data_temp[0], data_temp[1], data_temp[2], data_temp[3]);
			}
		}
	}
	else if constexpr (mla::CScalarExpression<_Type>) {
		auto data_temp = static_cast<const _Type*>(data);
		if constexpr (_Count > 1) {
			get_gl_set_uniform<_Type, 1, _Count>::value(location, _Count, data_temp);
		}
		else if constexpr (_Count == 1) {
			get_gl_set_uniform<_Type, 1, 1>::value(location, data_temp[0]);
		}
	}
	else {

	}
}

}
NGL_END
