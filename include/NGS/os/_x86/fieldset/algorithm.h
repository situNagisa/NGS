#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<fieldset T>
constexpr ::std::size_t bit_width()
{
	::std::size_t result = 0;
	for (auto&& i : NGS_LIB_MODULE_NAME::field_v<T>())
	{
		result += i;
	}
	return result;
}



template<fieldset T>
constexpr auto fieldset_value(auto&& physical_model) requires ::std::is_standard_layout_v<T>
{
	
}

NGS_LIB_MODULE_END