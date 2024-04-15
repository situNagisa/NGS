#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct page_table_entry
{
	NGS_MPL_ENVIRON_BEGIN(page_table_entry);
public:
	using underlying_type = ::std::uint32_t;

	underlying_type present : 1;
	underlying_type read_write : 1;
	underlying_type user_supervisor : 1;
	underlying_type page_level_write_through : 1;
	underlying_type page_level_cache_disable : 1;
	underlying_type accessed : 1;
	underlying_type dirty : 1;
	underlying_type pat : 1;
	underlying_type global : 1;
	underlying_type ignored : 3;
	underlying_type page_base_address : 20;
};

NGS_LIB_MODULE_END