#pragma once

#include "../granularity.h"
#include "./table.h"
#include "./directory.h"
#include "./address.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<granularity G>
constexpr decltype(auto) get_directory_entry(pointer_t visual, const ::std::span<const directory_entry>& directory_table)
{
	return directory_table[NGS_LIB_MODULE_NAME::page_directory_index<G>()];
}

template<granularity G>
constexpr decltype(auto) get_table_entry(pointer_t visual, const directory_entry& directory)
{
	::std::span page_table(reinterpret_cast<const table_entry*>(directory.base_address), directory.page_size() / sizeof(table_entry));
	return page_table[NGS_LIB_MODULE_NAME::page_table_index<G>()];
}

template<granularity G>
constexpr pointer_t addressing(pointer_t visual, const ::std::span<const directory_entry>& directory_table)
{
	auto offset = NGS_LIB_MODULE_NAME::page_offset<G>(visual);
	auto&& directory = NGS_LIB_MODULE_NAME::get_directory_entry<G>(visual, directory_table);

	if constexpr(G == granularity::bit)
	{
		auto&& table_entry = NGS_LIB_MODULE_NAME::get_table_entry<G>(visual, directory);
		return table_entry.base_address + offset;
		
	}
	else if constexpr (G == granularity::page)
	{
		return directory.base_address + offset;
	}
}

NGS_LIB_MODULE_END