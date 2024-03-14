#pragma once

#include "../enum.h"
#include "../context.h"
#include "../algorithm.h"
#include "./glsl.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template <template <auto...> class Template, auto... Args>
	void derived_from_basic_glsl(const Template<Args...>&);

	template <class T, template <auto...> class Template>
	concept glsl = requires(const T & obj) { _detail::derived_from_basic_glsl<Template>(obj); };

}

struct shader
{
	NGS_MPL_ENVIRON_BEGIN(shader);
public:
	using context_type = contexts::shader;

	explicit(false) shader(_detail::glsl<basic_glsl> auto&&... glsl)
	{
		((algorithm::shader_attach(_context, glsl.get_context())), ...);
		algorithm::shader_link(_context);
	}

	constexpr auto&& get_context()const { return _context; }

	context_type _context;
};

NGS_LIB_MODULE_END