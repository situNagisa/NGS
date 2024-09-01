#pragma once

#include "./uniform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<enums::buffer_uniform_fundamental T, ::std::size_t Dimension, bool Array = false>
	struct gl_uniform_map;

#define NGS_EXTERNAL_OPENGL_UNIFORM_MAP(type,type_id,dimension,...)					\
	template<>																		\
	struct gl_uniform_map<type, dimension __VA_OPT__(, true)>						\
	{																				\
		inline static auto&& value = ::glUniform##dimension##type_id##__VA_ARGS__;	\
	}																				\
//
#define NGS_EXTERNAL_OPENGL_UNIFORM_MAP_SEQUENCE(type,type_id,...)	\
	NGS_EXTERNAL_OPENGL_UNIFORM_MAP(type, type_id, 1, __VA_ARGS__);	\
	NGS_EXTERNAL_OPENGL_UNIFORM_MAP(type, type_id, 2, __VA_ARGS__);	\
	NGS_EXTERNAL_OPENGL_UNIFORM_MAP(type, type_id, 3, __VA_ARGS__);	\
	NGS_EXTERNAL_OPENGL_UNIFORM_MAP(type, type_id, 4, __VA_ARGS__)	\
//

	NGS_EXTERNAL_OPENGL_UNIFORM_MAP_SEQUENCE(enums::buffer_uniform_fundamental::floating_point, f);
	NGS_EXTERNAL_OPENGL_UNIFORM_MAP_SEQUENCE(enums::buffer_uniform_fundamental::floating_point, f, v);
	NGS_EXTERNAL_OPENGL_UNIFORM_MAP_SEQUENCE(enums::buffer_uniform_fundamental::integral, i);
	NGS_EXTERNAL_OPENGL_UNIFORM_MAP_SEQUENCE(enums::buffer_uniform_fundamental::integral, i, v);
	NGS_EXTERNAL_OPENGL_UNIFORM_MAP_SEQUENCE(enums::buffer_uniform_fundamental::unsigned_integral, ui);
	NGS_EXTERNAL_OPENGL_UNIFORM_MAP_SEQUENCE(enums::buffer_uniform_fundamental::unsigned_integral, ui, v);
	
#undef NGS_EXTERNAL_OPENGL_UNIFORM_MAP_SEQUENCE
#undef NGS_EXTERNAL_OPENGL_UNIFORM_MAP

#define glUniformMatrix2x2fv glUniformMatrix2fv
#define glUniformMatrix3x3fv glUniformMatrix3fv
#define glUniformMatrix4x4fv glUniformMatrix4fv

	template<enums::buffer_uniform_fundamental T, ::std::size_t Major, ::std::size_t Minor>
	struct gl_matrix_uniform_map;

#define NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP(type,type_id,major,minor)				\
	template<>																			\
	struct gl_matrix_uniform_map<type, major, minor>									\
	{																					\
		inline static auto&& value = ::glUniformMatrix##major##x##minor##type_id##v;	\
	}																					\
//
#define NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP_SEQUENCE(type,type_id)	\
	NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP(type, type_id, 2, 2);		\
	NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP(type, type_id, 2, 3);		\
	NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP(type, type_id, 2, 4);		\
	NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP(type, type_id, 3, 2);		\
	NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP(type, type_id, 3, 3);		\
	NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP(type, type_id, 3, 4);		\
	NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP(type, type_id, 4, 2);		\
	NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP(type, type_id, 4, 3);		\
	NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP(type, type_id, 4, 4)			\
//
	
	NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP_SEQUENCE(enums::buffer_uniform_fundamental::floating_point, f);

#undef NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP_SEQUENCE
#undef NGS_EXTERNAL_OPENGL_MATRIX_UNIFORM_MAP
#undef glUniformMatrix2x2fv
#undef glUniformMatrix3x3fv
#undef glUniformMatrix4x4fv
}


inline constexpr struct
{
	void _set(::std::ptrdiff_t location, auto first, auto... value)const
	{
		_detail::gl_uniform_map<
			reflects::buffers::uniform::reflect<decltype(first)>::value,
			sizeof...(value) + 1,
			false>::value(static_cast<GLint>(location), first, value...);
	}

	void operator()(::std::ptrdiff_t location, scalar auto value) const { this->_set(location, value); }
	template<scalar T>
	void operator()(::std::ptrdiff_t location, T _1, ::std::type_identity_t<T> _2) const { this->_set(location, _1, _2); }
	template<scalar T>
	void operator()(::std::ptrdiff_t location, T _1, ::std::type_identity_t<T> _2, ::std::type_identity_t<T> _3) const { this->_set(location, _1, _2, _3); }
	template<scalar T>
	void operator()(::std::ptrdiff_t location, T _1, ::std::type_identity_t<T> _2, ::std::type_identity_t<T> _3, ::std::type_identity_t<T> _4) const { this->_set(location, _1, _2, _3, _4); }

	void operator()(::std::ptrdiff_t location, const ::std::ranges::contiguous_range auto& data) const
		requires uniform<::std::ranges::range_value_t<decltype(data)>>
	{
		using range_value_type = ::std::ranges::range_value_t<decltype(data)>;
		if constexpr (scalar<range_value_type>)
		{
			_detail::gl_uniform_map<reflects::buffers::uniform::reflect<range_value_type>::value,1,true>::value(static_cast<GLint>(location), static_cast<GLsizei>(::std::ranges::size(data)), ::std::ranges::data(data));
		}
		if constexpr (vector<range_value_type>)
		{
			_detail::gl_uniform_map<
				reflects::buffers::uniform::reflect<typename vector_trait<range_value_type>::value_type>::value,
				vector_trait<range_value_type>::dimension(),
				true>::value(static_cast<GLint>(location), static_cast<GLsizei>(::std::ranges::size(data)), ::std::ranges::data(::std::ranges::begin(data)[0]));
		}
		if constexpr (matrix<range_value_type>)
		{
			(*this)(location, data, false);
		}
	}
	void operator()(::std::ptrdiff_t location, const ::std::ranges::contiguous_range auto& data, bool transpose)const
		requires matrix<::std::ranges::range_value_t<decltype(data)>>
	{
		_detail::gl_matrix_uniform_map<
			reflects::buffers::uniform::reflect<typename matrix_trait<::std::ranges::range_value_t<decltype(data)>>::value_type>::value,
			matrix_trait<::std::ranges::range_value_t<decltype(data)>>::major(),
			matrix_trait<::std::ranges::range_value_t<decltype(data)>>::minor()
		>::value(static_cast<GLint>(location), static_cast<GLsizei>(::std::ranges::size(data)), transpose, ::std::ranges::data(::std::ranges::begin(::std::ranges::begin(data)[0])[0]));
	}
}set_uniform{};

NGS_LIB_MODULE_END