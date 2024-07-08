#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t BitSize>
struct special_purpose : basic_register<BitSize>
{
	NGS_PP_INJECT(special_purpose);
};

NGS_OS_X86_REGISTER(special_purpose);

struct ip : special_purpose<16> {};
struct eip : special_purpose<32> {};

NGS_LIB_MODULE_END