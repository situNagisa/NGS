#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct table_entry
{
	::std::uint32_t p : 1;
	::std::uint32_t rw : 1;
	::std::uint32_t us : 1;
	::std::uint32_t pwt : 1;
	::std::uint32_t pcd : 1;
	::std::uint32_t a : 1;
	::std::uint32_t d : 1;
	::std::uint32_t pat : 1;

	::std::uint32_t g : 1;
	::std::uint32_t avl : 3;

	::std::uint32_t base : 20;

};

NGS_LIB_MODULE_END