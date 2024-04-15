#pragma once

#include "../../interrupt.h"
#include "./span.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct interrupt_descriptor_table : _detail::basic_span_register
{
	NGS_MPL_ENVIRON(interrupt_descriptor_table);
public:
	[[nodiscard]] auto range()const noexcept
	{
		return ::std::span{ reinterpret_cast<interrupts::gate_descriptor*>(address()), size / sizeof(interrupts::gate_descriptor)};
	}
};

NGS_LIB_MODULE_END
