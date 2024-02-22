#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct context : bases::delete_copy
{
	NGS_MPL_ENVIRON_BEGIN(context);
public:
	constexpr context(const context_t& context) noexcept : _context(context) {}

	constexpr auto&& get_context() const noexcept { return _context; }

	constexpr void _set_context(const context_t& c) { _context = c; }
private:
	context_t _context{};
};

NGS_LIB_MODULE_END