#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T, class Indices>
concept accessable = requires(T t, Indices indices)
{
	{ access(NGS_PP_PERFECT_FORWARD(t), NGS_PP_PERFECT_FORWARD(indices)) };
};

template<class T, class Indices = void>
concept tensor = 
	shapes::shape<tensor_extents_t<T>>
	&& (
		(::std::same_as<Indices, void> && accessable<T, ::std::array<shapes::shape_index_t<tensor_extents_t<T>>, shapes::rank(shapes::shape_ranks_v<tensor_extents_t<T>>)>>)
		|| accessable<T, Indices>
		)
;

NGS_LIB_MODULE_END