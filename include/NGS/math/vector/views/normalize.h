#pragma once

#include "../extent.h"
#include "../norm.h"
#include "../param_trait.h"
#include "../iterator.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<input_vector _V>
struct normalize_view : basic_vector, ::std::ranges::view_base, ::std::ranges::view_interface<normalize_view<_V>>
{
	using trait_type = param_trait<_V>;
	using norm_type = decltype(NGS_LIB_NAME::norm(::std::declval<typename trait_type::decay>()));
	constexpr static auto dereference(index_t index, typename trait_type::const_pointer vector, norm_type norm)
	{
		return NGS_LIB_NAME::random_access(*vector, index) / norm;
	}
	using value_type = decltype(normalize_view::dereference(0, nullptr, ::std::declval<norm_type>()));
	using iterator = vector_iterator<value_type, dereference, typename trait_type::const_pointer, norm_type>;
	constexpr static auto extent = extent_v<typename trait_type::type>;

	constexpr explicit(false) normalize_view(typename trait_type::param vector)
		: _vector(&vector)
		, _norm(NGS_LIB_NAME::norm(*_vector))
	{}

	constexpr auto begin()const { return iterator(0, _vector, _norm); }
	constexpr auto end()const { return iterator(::std::ranges::size(*_vector), _vector, _norm); }

	NGS_EXTERN_STL_RANGE_INPUT_ITERATOR();

public:
	typename trait_type::const_pointer _vector;
	norm_type _norm;
};

constexpr auto normalize(input_vector auto&& vector)
{
	return normalize_view<decltype(vector)>(NGS_PP_PERFECT_FORWARD(vector));
}



NGS_LIB_MODULE_END