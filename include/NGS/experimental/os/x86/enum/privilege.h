#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

enum class privilege
{
	ring0,
	ring1,
	ring2,
	ring3
};

constexpr auto operator<=>(privilege left, privilege right)
{
	return static_cast<::std::underlying_type_t<privilege>>(right) <=> static_cast<::std::underlying_type_t<privilege>>(left);
}

constexpr auto high(privilege left, privilege right) { return ::std::max(left, right); }
constexpr auto low(privilege left, privilege right) { return ::std::min(left, right); }



enum class page_privilege
{
	supervisor,
	user,
};

constexpr auto operator<=>(page_privilege left, page_privilege right)
{
	return static_cast<::std::underlying_type_t<page_privilege>>(right) <=> static_cast<::std::underlying_type_t<page_privilege>>(left);
}
constexpr auto high(page_privilege left, page_privilege right) { return ::std::max(left, right); }
constexpr auto low(page_privilege left, page_privilege right) { return ::std::min(left, right); }

NGS_LIB_END
