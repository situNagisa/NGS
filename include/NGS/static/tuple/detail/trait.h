#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class Tuple>
	requires experimental::templates::pure_type_template<::std::remove_cvref_t<Tuple>>
using as_std_t = type_traits::add_cvref_like_t<experimental::templates::pure_type_rep_temp_t<::std::remove_cvref_t<Tuple>, ::std::tuple>, Tuple>;

namespace detail_get
{
	//for ADL
	void get();

	template<class T, ::std::size_t I>
	concept get_has_member = requires(T tuple) { NGS_PP_PERFECT_FORWARD(tuple).template get<I>(); };

	template<class T, ::std::size_t I>
	concept get_has_adl = requires(T tuple) { get<I>(NGS_PP_PERFECT_FORWARD(tuple)); };

	template<::std::size_t I>
	struct get_cpo
	{
		constexpr decltype(auto) operator()(auto&& tuple)const noexcept requires get_has_member<decltype(tuple), I> || get_has_adl<decltype(tuple), I>
		{
			if constexpr (get_has_member<decltype(tuple), I>)
			{
				return NGS_PP_PERFECT_FORWARD(tuple).template get<I>();
			}
			else if constexpr (get_has_adl<decltype(tuple), I>)
			{
				return get<I>(NGS_PP_PERFECT_FORWARD(tuple));
			}
			else
			{
				static_assert(
					concepts::none<decltype(tuple)>,
					"tuple does not have get method"
					);
			}
		}
	};
}

template<::std::size_t I>
inline constexpr detail_get::get_cpo<I> get{};

template<::std::size_t I, experimental::templates::pure_type_template Tuple>
using element_t = ::std::tuple_element_t<I, as_std_t<Tuple>>;

template<experimental::templates::pure_type_template Tuple>
inline constexpr auto size_v = ::std::tuple_size_v<as_std_t<Tuple>>;

template<experimental::templates::pure_type_template... Tuples>
using cat_t = decltype(::std::tuple_cat(::std::declval<as_std_t<Tuples>>()...));


NGS_LIB_MODULE_END