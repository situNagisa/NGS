#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct cr0
{
	::std::uint32_t pe : 1;
	::std::uint32_t mp : 1;
	::std::uint32_t em : 1;
	::std::uint32_t ts : 1;
	::std::uint32_t et : 1;
	::std::uint32_t ne : 1;

	::std::uint32_t : 10;

	::std::uint32_t wp : 1;

	::std::uint32_t : 1;

	::std::uint32_t am : 1;

	::std::uint32_t : 10;

	::std::uint32_t nw : 1;
	::std::uint32_t cd : 1;
	::std::uint32_t pg : 1;
};

using cr1 = ::std::uint32_t;

using cr2 = ::std::uint32_t;

struct cr3
{
	::std::uint32_t : 3;
	::std::uint32_t pwt : 1;
	::std::uint32_t pcd : 1;
	::std::uint32_t : 7;
	::std::uint32_t base : 20;
};

struct cr4
{
	::std::uint32_t vme : 1;
	::std::uint32_t pvi : 1;
	::std::uint32_t tsd : 1;
	::std::uint32_t de : 1;
	::std::uint32_t pse : 1;
	::std::uint32_t pae : 1;
	::std::uint32_t mce : 1;
	::std::uint32_t pge : 1;

	::std::uint32_t pce : 1;
	::std::uint32_t osfxsr : 1;
	::std::uint32_t osxmmexcpt : 1;
	::std::uint32_t : 2;
	::std::uint32_t vmxe : 1;
	::std::uint32_t smxe : 1;
	::std::uint32_t : 2;
	::std::uint32_t pcide : 1;
	::std::uint32_t osxsave : 1;
	::std::uint32_t : 1;
	::std::uint32_t smep : 1;
};

NGS_LIB_MODULE_END
