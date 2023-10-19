#pragma once

#include "../defined.h"
#include "../attrib/dynamic_data.h"

NGS_NGL_FUSION_BEGIN

template<class _Buffer>
concept CBuffer = requires() {
	typename _Buffer::element_type;
	{ _Buffer::element_count } -> std::convertible_to<size_t>;
	{ _Buffer::attrib_count } -> std::convertible_to<size_t>;
	{ _Buffer::GET_ATTRIBS() } -> std::convertible_to<std::array<attrib_dynamic_data, _Buffer::attrib_count>>;
		requires mpl::mstruct::CStructure<_Buffer>;
};

NGS_NGL_FUSION_END
