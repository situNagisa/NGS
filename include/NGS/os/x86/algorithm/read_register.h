#pragma once

#include "../register.h"
#include "../asm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<registers::register_ T>
constexpr decltype(auto) read_register()
{
	auto value = asms::read<registers::register_category_t<T>>();
	return *reinterpret_cast<type_traits::object_t<T>*>(&value);
}

NGS_LIB_MODULE_END