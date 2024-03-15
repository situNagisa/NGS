#pragma once

#include "../storage.h"
#include "./concept.h"
#include "./field_at.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


namespace _detail
{
	template<statics::strings::string Name,::std::size_t Index, class... Fields>
	struct find_index;

	template<statics::strings::string Name,::std::size_t Index, class First, class... Rest>
	struct find_index<Name, Index, First, Rest...>
	{
		constexpr static auto value = (static_cast<::std::string_view>(named_pair_name_t<First>::value) == static_cast<::std::string_view>(Name)) ? Index : find_index<Name, Index + 1, Rest...>::value;
	};

	template<statics::strings::string Name, ::std::size_t Index>
	struct find_index<Name, Index>
	{
		constexpr static auto value = static_cast<::std::size_t>(-1);
	};

	template<statics::strings::string, class>
	struct get_index {};

	template<statics::strings::string Name, template<class...>class Template, class... Field>
	struct get_index<Name, Template<Field...>>
	{
		constexpr static auto value = find_index<Name,0, Field...>::value;
	};

	template<statics::strings::string Name, class Fields>
	inline constexpr ::std::size_t get_index_v = get_index<Name, Fields>::value;
}

template<statics::strings::string Name>
constexpr decltype(auto) get(named_structure auto&& s) requires (_detail::get_index_v<Name,struct_named_fields_t<decltype(s)>> < basic::struct_size_v<decltype(s)>)
{
	return storages::get<_detail::get_index_v<Name, struct_named_fields_t<decltype(s)>>>(NGS_PP_PERFECT_FORWARD(s));
}

NGS_LIB_MODULE_END