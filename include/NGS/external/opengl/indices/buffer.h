#pragma once

#include "../buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class IndexType>
struct buffer : buffers::unique_buffer<enums::buffer_target::element,IndexType>
{
	NGS_MPL_ENVIRON2(buffer, buffers::unique_buffer<enums::buffer_target::element, IndexType>);
public:
	using index_type = IndexType;

	using base_type::base_type;
	using base_type::operator=;
};

NGS_LIB_MODULE_END