#pragma once

#include "./rank.h"
#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept shape = 
	ranks<decltype(shape_ranks_v<T>)>
	&& requires(T t, rank_t index) { { extent_at(NGS_PP_PERFECT_FORWARD(t), index) } -> ::std::convertible_to<shape_index_t<T>>; }
	&& ::std::regular<::std::remove_cvref_t<T>>
	&& ::std::is_trivially_copyable_v<::std::remove_cvref_t<T>>
	;

template<class T, class Other>
concept common_index = ::std::convertible_to<Other, T>&& ::std::is_nothrow_constructible_v<T, Other>;

NGS_LIB_MODULE_END