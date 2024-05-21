#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t BitSize>
struct index : basic_register<BitSize>
{
	NGS_PP_INJECT(index);
};

NGS_OS_X86_REGISTER(index);

struct si : index<16> {};
struct esi : index<32> {};

struct di : index<16> {};
struct edi : index<32> {};

NGS_LIB_MODULE_END