#pragma once

#include "../granularity.h"
#include "./enum_under.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct page_directory_entry_4kb
{
	NGS_MPL_ENVIRON_BEGIN(page_directory_entry_4kb);
public:
	using underlying_type = ::std::uint32_t;

	underlying_type present : 1;
	underlying_type read_write : 1;
	underlying_type user_supervisor : 1;
	underlying_type page_level_write_through : 1;
	underlying_type page_level_cache_disable : 1;
	underlying_type accessed : 1;
	underlying_type dirty : 1;
	underlying_type page_size : 1;
	underlying_type ignored : 4;
	underlying_type table_base_address : 20;
};


struct page_directory_entry_4mb
{
	NGS_MPL_ENVIRON_BEGIN(page_directory_entry_4mb);
public:
	using underlying_type = ::std::uint32_t;

	underlying_type present : 1;
	underlying_type read_write : 1;
	underlying_type user_supervisor : 1;
	underlying_type page_level_write_through : 1;
	underlying_type page_level_cache_disable : 1;
	underlying_type accessed : 1;
	underlying_type dirty : 1;
	underlying_type page_size : 1;
	underlying_type global : 1;
	underlying_type ignored : 3;
	underlying_type pat : 1;
	underlying_type offset : 4;
	underlying_type : 5;
	underlying_type page_base_address : 10;
};

template<granularity G>
using page_directory_entry = ::std::conditional_t<G == granularity::bit, page_directory_entry_4kb, page_directory_entry_4mb>;

NGS_LIB_MODULE_END