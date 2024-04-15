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

constexpr bool operator==(privilege left, privilege right)
{
	return left <=> right == 0;
}

NGS_LIB_END
