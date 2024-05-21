#pragma once

#include "../page_size.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct page_directory_entry_4kb
{
	NGS_PP_INJECT_BEGIN(page_directory_entry_4kb);
public:
	using underlying_type = ::std::uint32_t;

	underlying_type present : 1;
	underlying_type access_type : 1;
	underlying_type user_supervisor : 1;
	underlying_type page_level_write_through : 1;
	underlying_type page_level_cache_disable : 1;
	underlying_type accessed : 1;
	underlying_type dirty : 1;
	underlying_type page_size : 1 = static_cast<underlying_type>(NGS_LIB_NAME::page_size::_4kb);
	underlying_type ignored : 4;
	underlying_type table_base : 20;
};


struct page_directory_entry_4mb
{
	NGS_PP_INJECT_BEGIN(page_directory_entry_4mb);
public:
	using underlying_type = ::std::uint32_t;

	underlying_type present : 1;
	underlying_type access_type : 1;
	underlying_type user_supervisor : 1;
	underlying_type page_level_write_through : 1;
	underlying_type page_level_cache_disable : 1;
	underlying_type accessed : 1;
	underlying_type dirty : 1;
	underlying_type page_size : 1 = static_cast<underlying_type>(NGS_LIB_NAME::page_size::_4mb);
	underlying_type global : 1;
	underlying_type ignored : 3;
	underlying_type pat : 1;
	underlying_type offset : 4;
	underlying_type : 5;
	underlying_type page_base : 10;
};

template<page_size Size>
using page_directory_entry = ::std::conditional_t<Size == page_size::_4kb, page_directory_entry_4kb, page_directory_entry_4mb>;

NGS_LIB_MODULE_END