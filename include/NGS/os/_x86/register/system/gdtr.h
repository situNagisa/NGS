#pragma once

#include "../../segment.h"
#include "./span.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct global_descriptor_table : _detail::basic_span_register
{
	NGS_MPL_ENVIRON(global_descriptor_table);
public:
	
	[[nodiscard]] auto range()const noexcept
	{
		return ::std::span{ reinterpret_cast<segments::descriptor*>(address()), size / sizeof(segments::descriptor)};
	}
};

NGS_LIB_MODULE_END