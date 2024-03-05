#pragma once

#include "./variable.h"
#include "./fields.h"
#include "../basic.h"
#include "../algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<layout::align auto Align, variables::variable... Variables>
	struct descriptor
	{
		NGS_MPL_ENVIRON_BEGIN(descriptor);
	public:
		using fields_type = fields<Variables...>;
		static constexpr ::std::size_t field_count = sizeof...(Variables);

		static constexpr layout::align_t align = layout::align_of(Align, variables::variable_align_v<Variables>...);
		
		static constexpr ::std::size_t size = layout::size_of<align.align()>(variables::variable_size_v<Variables>...);

		template<basic::reflecter Reflecter>
		static constexpr auto reflect()
		{
			constexpr auto offsets = layout::offset<align.align()>(variables::variable_size_v<Variables>...);
			constexpr auto types = ::std::array{ static_cast<typename Reflecter::type>(Reflecter::template reflect<variables::variable_value_t<Variables>>::value)... };
			return[]<::std::size_t... Index>(::std::index_sequence<Index...>)
			{
				return ::std::array<basic::reflect_data<typename Reflecter::type>, field_count>{
					basic::reflect_data{
						variables::variable_size_v<Variables>,
						offsets[Index],
						types[Index]
					}...
				};
			}(::std::make_index_sequence<field_count>{});
		}
	};

	template<templates::template_class T>
	struct variable_sequence : ::std::false_type {};

	template<template<class...>class Container, variables::variable... Fields>
	struct variable_sequence<Container<Fields...>> : ::std::true_type {};

	template<class T>
	concept fields = variable_sequence<T>::value;

	template<template<auto, class...>class Struct, auto Align, class Fields>
	struct make_struct {};
	template<template<auto, class...>class Struct, auto Align, template<class...>class FieldContainer, class... Fields>
	struct make_struct<Struct, Align, FieldContainer<Fields...>>
	{
		using type = Struct<Align, Fields...>;
	};
	
	template<basic::structure T, basic::structure... Bases>
	struct inherit {};

	template<basic::structure T>
	struct inherit<T> { using type = T; };

	template<template<auto, class...>class Struct, auto Align, class... Ts, basic::structure... Bases>
	struct inherit<Struct<Align, Ts...>, Bases...>
	{
		using derived_type = Struct<Align, Ts... >;
		using type = typename make_struct<
			Struct,
			layout::align_of(basic::struct_align_v< derived_type>, basic::struct_align_v<Bases>...),
			external::nboost::fusion::result_of::cat_t<::boost::fusion::vector, basic::fields_t<Bases>..., basic::fields_t<derived_type>>
		>::type;
	};
}

template<layout::align auto, _detail::fields> struct basic_struct {};
template<layout::align auto Align, template<class...>class Container, class... Fields>
struct basic_struct<Align, Container<Fields...>> : _detail::descriptor<Align, Fields...>
{
	NGS_MPL_ENVIRON(basic_struct);
public:
	template<class... Bases>
	struct inherit : _detail::inherit<self_type, Bases...>::type {};
};

template<layout::align auto Align, class... Ts>
struct meta_struct : basic_struct<Align,make_fields_t<Ts...>>
{
	NGS_MPL_ENVIRON(meta_struct);
};


NGS_LIB_MODULE_END
NGS_LIB_BEGIN

template<template<auto,class...>class Struct,auto Align,class... Ts> requires basic::structure<Struct<Align,Ts...>>
struct algorithm::flatten<Struct<Align, Ts...>>
{
	using struct_type = Struct<Align, Ts...>;
	using type = NGS_LIB_MODULE_NAME::basic_struct<basic::struct_align_v<struct_type>, flatten_as_sequence_t<struct_type>>;
};

NGS_LIB_END