#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept enumerated = ::std::is_enum_v<T>;

namespace _detail
{
	template<auto V>
	consteval auto is_named_enum()
	{
		constexpr auto name = symbols::field_symbol_name<V>();
		return ::std::ranges::find(name, '(') == ::std::ranges::end(name);
	}
}

template<auto Value>
concept named_field = enumerated<decltype(Value)> && _detail::is_named_enum<Value>();

NGS_LIB_MODULE_END