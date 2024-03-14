#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using context_t = GLuint;
inline constexpr context_t null_context = static_cast<context_t>(0);

struct context : bases::delete_copy
{
	NGS_MPL_ENVIRON_BEGIN(context);
public:
	constexpr explicit(false) context(const context_t& context) noexcept : _context(context) {}
	constexpr context(self_type&& other)noexcept : _context(other._context)
	{
		other._context = 0;
	}
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
	constexpr ~context()
	{
		_context = 0;
	}
#endif
	constexpr self_type& operator=(self_type&& other) noexcept
	{
		if (!::std::is_constant_evaluated())
			NGS_EXPECT(_context == 0);
		_context = other._context;
		other._context = 0;
		return *this;
	}

	constexpr auto&& get_context() const noexcept { return _context; }

	constexpr void _set_context(const context_t& c) { _context = c; }
private:
	context_t _context{};
};

NGS_LIB_MODULE_END