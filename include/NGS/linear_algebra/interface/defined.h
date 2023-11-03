#pragma once

#include "../defined.h"

#define NGS_MATH_LA_INTERFACE_BEGIN NGS_MATH_LA_BEGIN namespace interfaces {
#define NGS_MATH_LA_INTERFACE_END } NGS_MATH_LA_END
#define NGS_MATH_LA_ADAPTER_BEGIN NGS_MATH_LA_BEGIN namespace adapters {
#define NGS_MATH_LA_ADAPTER_END } NGS_MATH_LA_END
#define NGS_MATH_LA_TRAIT_BEGIN NGS_MATH_LA_BEGIN namespace traits {
#define NGS_MATH_LA_TRAIT_END } NGS_MATH_LA_END

//cnmd windows
#undef interface

NGS_MATH_LA_ADAPTER_BEGIN

enum class functor_choice
{
	none,
	interface,
	member,
	operators,
	other,
};

NGS_MATH_LA_ADAPTER_END