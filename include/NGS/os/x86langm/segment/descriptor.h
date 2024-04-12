#pragma once

#include "../pointer.h"
#include "../privilege.h"
#include "../bit_width.h"
#include "../granularity.h"
#include "./mode.h"
#include "./type.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct descriptor
{
	type type;

	::std::uint16_t size;
	pointer_t base_address;

	bool present;
	privilege privilege;
	granularity granularity;
	mode mode;

	union
	{
		struct _data
		{
			bool accessed;
			bool writable;
			bool expand_down;

		}data;
		struct _code
		{
			bool accessible;
			bool conforming;
			bool readable;
			bit_width operation_size;
		}code;
		struct _ldt{} ldt;
		struct _tss
		{
			bool busy;
			bit_width bit_width;
		}tss;
		struct _gate_task{} gate_task;
		struct _gate
		{
			bit_width bit_width;
		}gate_call,gate_interrupt,gate_trap;
	};

	constexpr auto segment_size() const { return size * NGS_LIB_NAME::granularity_factor(granularity); }

	auto segment_range()
	{
		return ::std::span(reinterpret_cast<byte*>(base_address), segment_size());
	}
	auto segment_range() const
	{
		return ::std::span(reinterpret_cast<const byte*>(base_address), segment_size());
	}
};

NGS_LIB_MODULE_END