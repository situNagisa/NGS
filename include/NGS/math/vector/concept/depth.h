#pragma once

#include "../tag.h"
#include "../anchor.h"
#include "../depth.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _V> concept range_vector = ::std::ranges::random_access_range<_V>;
template<class _V> concept tuple_vector = ::std::derived_from<NGS_MATH_VECTOR_TAG_NS::trait_t<_V>, NGS_MATH_VECTOR_TAG_NS::vector>&& statics::tuples::tuple_like<_V>;

template<class _V>
concept generalized_vector = range_vector<_V>;// || tuple_vector<_V>;

template<class _V>
concept pure_vector = generalized_vector<_V> && depth_v<_V> == 1;

template<class _V>
concept non_vector = !generalized_vector<_V>;

template<class _T>
concept scalar = non_vector<_T> && (::std::is_scalar_v<type_traits::naked_t<_T>> || cpt::is_specialization_of<type_traits::naked_t<_T>, ::std::complex>);

template<class _V>
concept scalar_vector = pure_vector<_V> && scalar<::std::ranges::range_value_t<_V>>;

NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(pure_vector);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(generalized_vector);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(non_vector);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(scalar);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(scalar_vector);

NGS_LIB_MODULE_END
NGS_LIB_BEGIN

template<range_vector _V>
struct depth<_V> : ccpt::constant_<depth_t, depth_v<value_t<_V>> +1> {};

namespace detail
{
	constexpr depth_t min() { return 0; }
	constexpr depth_t min(auto first) { return first; }
	constexpr depth_t min(auto first, auto second, auto... args)
	{
		if constexpr (sizeof...(args))
		{
			return detail::min(first < second ? first : second, args...);
		}
		else
		{
			return first < second ? first : second;
		}
	}

	template<class _Tuple, class = ::std::make_index_sequence<extent_v<_Tuple>>>
	struct tuple_depth {};

	template<class _Tuple, size_t... _Index>
	struct tuple_depth<_Tuple, ::std::index_sequence<_Index...>>
	{
		constexpr static extent_t value = 1 + detail::min(depth_v<value_t<_Tuple, _Index>>...);
	};
}

//template<tuple_vector _V>
//struct depth<_V> : ccpt::constant_<depth_t, detail::tuple_depth<_V>::value> {};

NGS_LIB_END