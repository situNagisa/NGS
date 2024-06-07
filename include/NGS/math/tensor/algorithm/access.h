#pragma once

#include "../trait.h"
#include "../concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

inline constexpr struct
{
	template<concepts::tensor T>
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(T&& tensor, )
}access{};

NGS_LIB_MODULE_END
