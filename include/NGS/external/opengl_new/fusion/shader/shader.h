#pragma once

#include "../../enum.h"
#include "../../context.h"
#include "./glsl.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template <auto Args>
	void derived_from_basic_glsl(const basic_glsl<Args>&);

	template <class T>
	concept glsl = requires(const T & obj) { _detail::derived_from_basic_glsl(obj); };

}

struct shader
{
	NGS_MPL_ENVIRON_BEGIN(shader);
public:
	using context_type = contexts::shader;

	explicit(false) shader(_detail::glsl auto&&... glsl)
	{
		((_context.attach(glsl.get_context())), ...);
		_context.link();
	}

	constexpr auto&& get_context()const { return _context; }

	auto get_uniform_location(::std::string_view name)const
	{
		return _context.get_uniform_location(name);
	}

	template<reflects::buffer_uniform T>
	void set_uniform(::std::ptrdiff_t location, T value)const { _context.set_uniform(location, value); }
	template<reflects::buffer_uniform T>
	void set_uniform(::std::ptrdiff_t location, T value1, ::std::type_identity_t<T> value2)const { _context.set_uniform(location, value1, value2); }
	template<reflects::buffer_uniform T>
	void set_uniform(::std::ptrdiff_t location, T value1, ::std::type_identity_t<T> value2, ::std::type_identity_t<T> value3)const { _context.set_uniform(location, value1, value2, value3); }
	template<reflects::buffer_uniform T>
	void set_uniform(::std::ptrdiff_t location, T value1, ::std::type_identity_t<T> value2, ::std::type_identity_t<T> value3, ::std::type_identity_t<T> value4)const { _context.set_uniform(location, value1, value2, value3, value4); }

	void set_uniform(::std::ptrdiff_t location, const contexts::shader_uniform auto& data)const { _context.set_uniform(location, data); }

	context_type _context;
};

NGS_LIB_MODULE_END