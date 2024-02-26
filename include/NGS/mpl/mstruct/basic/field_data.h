#pragma once

#include "../variable.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class T>
	concept field_data = requires(const T obj)
	{
		{ obj.size } -> std::convertible_to<::std::size_t>;
		{ obj.offset } -> std::convertible_to<::std::size_t>;
		{ obj.type } -> std::convertible_to<variables::variable_type_t>;
	};
}

template<class T>
concept field_data = ::std::ranges::range<T> && _detail::field_data<::std::ranges::range_value_t<T>>;

NGS_LIB_MODULE_END
