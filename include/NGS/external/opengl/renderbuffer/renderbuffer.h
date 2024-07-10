#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::renderbuffer_target Target>
struct basic_renderbuffer
{
	NGS_PP_INJECT_BEGIN(basic_renderbuffer);
public:
	using context_type = NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::basic_renderbuffer<Target>;

	basic_renderbuffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_internal_format format, ::std::size_t width, ::std::size_t height)
	{
		NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::bind(_context);
		self_type::storage(format, width, height);
	}

	void storage(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_internal_format format, ::std::size_t width, ::std::size_t height) const
	{
		_context.storage(format, width, height);
	}

	constexpr auto&& get_context() const { return _context; }

	context_type _context;
};

using renderbuffer = basic_renderbuffer<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::renderbuffer_target::renderbuffer>;

NGS_LIB_MODULE_END