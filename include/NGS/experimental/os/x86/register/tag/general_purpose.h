#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t BitSize>
struct general_purpose : basic_register<BitSize>
{
	NGS_PP_INJECT(general_purpose);
public:
};

NGS_OS_X86_REGISTER(general_purpose);

struct al : general_purpose<8> {};
struct ah : general_purpose<8> {};
struct ax : general_purpose<16> {};
struct eax : general_purpose<32> {};

struct bl : general_purpose<8> {};
struct bh : general_purpose<8> {};
struct bx : general_purpose<16> {};
struct ebx : general_purpose<32> {};

struct cl : general_purpose<8> {};
struct ch : general_purpose<8> {};
struct cx : general_purpose<16> {};
struct ecx : general_purpose<32> {};

struct dl : general_purpose<8> {};
struct dh : general_purpose<8> {};
struct dx : general_purpose<16> {};
struct edx : general_purpose<32> {};

NGS_LIB_MODULE_END