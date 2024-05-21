#pragma once

#include "../privilege.h"
#include "./descriptor.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct selector
{
	::std::uint16_t index;
	enum class table_indicator_t
	{
		global_descriptor_table = 0,
		local_descriptor_table = 1
	} table_indicator;
	privilege privilege;

	constexpr bool selectable(const descriptor& descriptor) const
	{
		return privilege >= descriptor.privilege;
	}

	constexpr auto&& select_table(const ::std::span<const descriptor>& global_descriptor_table, const ::std::span<const descriptor>& local_descriptor_table)const
	{
		return table_indicator == table_indicator_t::global_descriptor_table ? global_descriptor_table : local_descriptor_table;
	}

	constexpr auto&& select(::std::span<const descriptor> descriptor_table) const
	{
		return descriptor_table[index];
	}

	constexpr auto&& select(::std::span<descriptor> descriptor_table) const
	{
		return descriptor_table[index];
	}
};





NGS_LIB_MODULE_END