#pragma once

#include "./concept.h"
#include "./dynamic_data.h"
#include "../attrib/make.h"

NGS_NGL_FUSION_BEGIN

template<CBuffer _Buffer>
constexpr auto make_buffer() {
	buffer_dynamic_data data{
		.count = _Buffer::variable_count,
		.size = _Buffer::size,
		.properties = {},
	};
	std::ranges::copy(_Buffer::GET_ATTRIBS(), std::back_inserter(data.properties));

	return data;
}

NGS_NGL_FUSION_END
