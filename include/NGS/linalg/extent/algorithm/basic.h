#pragma once

#include "../trait.h"
#include "../concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr traits::static_extent_t compound_extent(traits::static_extent_t left, traits::static_extent_t right)
{
	return ::std::max(left, right);
}

template<concepts::shape T>
consteval traits::static_extent_t static_extent(traits::rank_t i)
{
	return traits::static_extent<type_traits::object_t<T>>::value(i);
}

using traits::extent;

template<concepts::shape T>
consteval traits::rank_t rank()
{
	return traits::rank<type_traits::object_t<T>>::value();
}

template<concepts::shape T>
consteval traits::rank_t rank_dynamic()
{
	return traits::rank_dynamic<type_traits::object_t<T>>::value();
}

template<concepts::shape T>
consteval traits::rank_t rank_adaptor()
{
	return traits::rank_adaptor<type_traits::object_t<T>>::value();
}

NGS_LIB_MODULE_END