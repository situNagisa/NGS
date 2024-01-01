#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<index_t _Index>
struct placeholder : std::integral_constant<index_t, _Index>
{
	static_assert(_Index > 0, "invalid placeholder index");
	using ngs_functional_parameter_packet_placeholder_tag = _detail::placeholder_tag;
};

NGS_LIB_MODULE_END
