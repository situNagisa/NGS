#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t BitSize>
struct state : basic_register<BitSize>
{
	NGS_PP_INJECT(state);
};

NGS_OS_X86_REGISTER(state);

struct flags : state<16> {};
struct eflags : state<32> {};

NGS_LIB_MODULE_END