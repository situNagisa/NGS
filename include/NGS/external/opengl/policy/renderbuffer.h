#pragma once

#include "../enum.h"
#include "../algorithm.h"
#include "../context.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<enums::renderbuffer_target Target>
struct basic_renderbuffer
{
	NGS_MPL_ENVIRON_BEGIN(basic_renderbuffer);
public:
	using context_type = contexts::basic_renderbuffer<Target>;

	basic_renderbuffer(enums::internal_format format, ::std::size_t width, ::std::size_t height)
	{
		basic::bind(_context);
		self_type::storage(format, width, height);
	}

	void storage(enums::internal_format format, ::std::size_t width, ::std::size_t height) const
	{
		algorithm::renderbuffer_storage(_context, format, width, height);
	}

	constexpr auto&& get_context() const { return _context; }

	context_type _context;
};

using renderbuffer = basic_renderbuffer<enums::renderbuffer_target::renderbuffer>;

NGS_LIB_MODULE_END