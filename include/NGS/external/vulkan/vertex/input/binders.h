#pragma once

#include "./binder.h"

NGS_LIB_MODULE_BEGIN

namespace detail {
	template<class...>
	struct binders;

	template<CBinder... _Binders>
	struct binders<_Binders...>
	{
		using structure_type = mpl::mstruct::flatten_as_struct_t<mpl::mstruct::structure<typename _Binders::structure_type...>>;

		constexpr static size_t binder_count = sizeof...(_Binders);
		constexpr static size_t attribute_count = (_Binders::attribute_count + ...);

		constexpr NGS_CONFIG_STATIC_23 decltype(auto) operator()(::std::span<VkVertexInputBindingDescription> infos)
#if !defined(NGS_CPP_STANDARD_HAS_23)
			const
#endif
		{
			[infos] <size_t... _Index>(::std::index_sequence<_Index...>) {
				((
					_Binders{}(infos[_Index]),
					infos[_Index].binding = static_cast<uint32_t>(_Index)
					), ...);
			}(::std::make_index_sequence<binder_count>());
			return infos;
		}
		constexpr NGS_CONFIG_STATIC_23 decltype(auto) operator()(::std::span<VkVertexInputAttributeDescription> infos)
#if !defined(NGS_CPP_STANDARD_HAS_23)
			const
#endif
		{
			constexpr auto binder_offset = layout::offset<layout::no_align>(_Binders::structure_type::size...);
			[infos] <size_t... _Index>(::std::index_sequence<_Index...>) {
				((
					_Binders{}(infos.subspan(binder_offset[_Index], _Binders::structure_type::size)),
					infos[_Index].binding = static_cast<uint32_t>(_Index)
					), ...);
			}(::std::make_index_sequence<binder_count>());
			return infos;
		}
	};

	template<class...> struct make_binders;

	template<class... _Types> using make_binders_t = typename make_binders<_Types...>::type;

	template<class>struct make_binder_from_sequence;
	template<template<class...>class _Template, class... _Types>
	struct make_binder_from_sequence<_Template<_Types...>>
	{
		using type = make_binder_t<_Types...>;
	};
	template<class... _Types> using make_binder_from_sequence_t = typename make_binder_from_sequence<_Types...>::type;

	template<class...> struct make_binders_sequence;
	template<class... _Types> using make_binders_sequence_t = typename make_binders_sequence<_Types...>::type;

	template<class... _Caches, class _First, class... _Types>
	struct make_binders_sequence<::boost::fusion::vector<_Caches...>, _First, _Types...>
	{
		using caches_type = ::boost::fusion::vector<_Caches...>;

		constexpr static auto get_cache_binder_type()
		{
			if constexpr (::boost::fusion::result_of::size<caches_type>::value)
			{
				return ngs::declval<::boost::fusion::vector<make_binder_from_sequence_t<caches_type>>>();
			}
			else
			{
				return ngs::declval<::boost::fusion::vector<>>();
			}
		}


		constexpr static auto get_type()
		{
			if constexpr (CBinder<_First>)
			{
				using cache_binder_type = type_traits::naked_t<decltype(get_cache_binder_type())>;
				using current_type = nboost::fusion::result_of::cat_t<cache_binder_type, ::boost::fusion::vector<_First>>;
				if constexpr (sizeof...(_Types))
				{
					using rest_type = make_binders_sequence_t<::boost::fusion::vector<>, _Types...>;
					return ngs::declval<nboost::fusion::result_of::cat_t<current_type, rest_type>>();
				}
				else
				{
					return ngs::declval<current_type>();
				}
			}
			else
			{
				using current_type = nboost::fusion::result_of::cat_t<caches_type, ::boost::fusion::vector<_First>>;
				if constexpr (sizeof...(_Types))
				{
					using rest_type = make_binders_sequence_t<current_type, _Types...>;
					return ngs::declval<rest_type>();
				}
				else
				{
					return ngs::declval<::boost::fusion::vector<make_binder_from_sequence_t<current_type>>>();
				}
			}
		}
		using type = type_traits::naked_t<decltype(get_type())>;
	};

	template<class>struct make_binders_from_sequence;
	template<template<class...>class _Template, CBinder... _Binders>
	struct make_binders_from_sequence<_Template<_Binders...>>
	{
		using type = binders<_Binders...>;
	};
	template<class... _Types> using make_binders_from_sequence_t = typename make_binders_from_sequence<_Types...>::type;

	template<class... _Types>
	struct make_binders
	{
		using type = make_binders_from_sequence_t<make_binders_sequence_t<::boost::fusion::vector<>, _Types...>>;
	};
}

template<class... _Types> using binders = detail::make_binders_t<_Types...>;

NGS_LIB_MODULE_END