#pragma once

#include "../granularity.h"
#include "../page_size.h"
#include "../pointer.h"
#include "./privilege.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


struct basic_entry
{
	NGS_PP_INJECT_BEGIN(basic_entry);
public:
	bool present;
	bool writable;
	page_privilege privilege;
	bool write_through;
	bool cache_disable;
	bool accessed;
	bool dirty;
	granularity granularity;
	bool global;
	pointer_t base_address;

	constexpr auto page_size() const
	{
		return NGS_LIB_NAME::page_size_factor(granularity);
	}

	auto page_range()
	{
		return ::std::span( reinterpret_cast<::std::byte*>(base_address), page_size() );
	}

	auto page_range() const
	{
		return ::std::span( reinterpret_cast<const ::std::byte*>(base_address), page_size() );
	}
};

NGS_LIB_MODULE_END