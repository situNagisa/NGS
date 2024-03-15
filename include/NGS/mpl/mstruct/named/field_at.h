#pragma once

#include "./field.h"
#include "./named_fields.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	consteval bool name_is_same(::std::string_view a,::std::string_view b)
	{
		return a == b;
	}

	template<statics::strings::string Name, class... Fields>
	struct find;

	template<statics::strings::string Name, class First, class... Rest>
	struct find<Name, First, Rest...>
	{
		using type = ::std::conditional_t<
			_detail::name_is_same(named_pair_name_t<First>::value, Name),
			First,
			typename find<Name, Rest...>::type
		>;
	};

	template<statics::strings::string Name>
	struct find<Name>
	{
		using type = void;
	};

	template<statics::strings::string, class>
	struct get_pair {};

	template<statics::strings::string Name, template<class...>class Template, class... Field>
	struct get_pair<Name, Template<Field...>>
	{
		using type = typename find<Name, Field...>::type;
	};

	template<statics::strings::string Name, class Struct>
	using get_pair_t = typename get_pair<Name, Struct>::type;

	template<class Pair>
	struct pair_value
	{
		using type = named_pair_field_t<Pair>;
	};
	template<>
	struct pair_value<void>
	{
		using type = void;
	};
}

template<class Struct, statics::strings::string Name>
struct named_field_at
{
	using type = typename _detail::pair_value<_detail::get_pair_t<Name, struct_named_fields_t<Struct>>>::type;
};

template<class Struct, statics::strings::string Name>
using named_field_at_t = typename named_field_at<Struct, Name>::type;

NGS_LIB_MODULE_END