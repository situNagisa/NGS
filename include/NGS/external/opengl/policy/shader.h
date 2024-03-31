#pragma once

#include "../enum.h"
#include "../context.h"
#include "../algorithm.h"
#include "./glsl.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template <auto... Args>
	void derived_from_basic_glsl(const basic_glsl<Args...>&);

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
		((algorithm::shader_attach(_context, glsl.get_context())), ...);
		algorithm::shader_link(_context);
	}

	constexpr auto&& get_context()const { return _context; }

	auto get_uniform_location(::std::string_view name)const
	{
		return algorithm::shader_get_uniform_location(_context, name);
	}

	void set_uniform(::std::ptrdiff_t location, const ::std::ranges::contiguous_range auto& data, ::std::ptrdiff_t offset = 0)
		requires algorithm::_detail::uniform<::std::ranges::range_value_t<decltype(data)>>
	{
		algorithm::shader_set_uniform(_context, location, data, offset);
	}
	void set_uniform(::std::ptrdiff_t location, const algorithm::_detail::uniform auto& data)
		requires algorithm::_detail::fundametal_uniform<::std::ranges::range_value_t<decltype(data)>>
	{
		algorithm::shader_set_uniform(_context, location, data);
	}

	context_type _context;
};

NGS_LIB_MODULE_END