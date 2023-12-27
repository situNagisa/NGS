#pragma once

#include "../extent.h"
#include "../norm.h"
#include "../param_trait.h"
#include "../iterator.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<input_vector _V>
struct normalize_view : basic_vector
{
	using trait_type = param_trait<_V>;
	using value_type = ::std::ranges::range_value_t<typename trait_type::type>;
	constexpr static auto extent = extent_v<typename trait_type::type>;

	constexpr explicit(false) normalize_view(typename trait_type::param vector)
		: _vector(NGS_PP_PERFECT_FORWARD(vector))
		, _norm(NGS_LIB_NAME::norm(_vector))
	{}

	constexpr static auto dereference(index_t index, typename trait_type::const_pointer vector, value_type norm)
	{
		return NGS_LIB_NAME::random_access(*vector, index) / norm;
	}
	using iterator = vector_iterator<const value_type, dereference, typename trait_type::const_pointer, value_type>;

	constexpr auto begin()const { return iterator(0, &_vector, _norm); }
	constexpr auto end()const { return iterator(NGS_LIB_NAME::size(_vector), &_vector, _norm); }

	NGS_EXTERN_STL_RANGE_INPUT_ITERATOR();

public:
	typename trait_type::decay _vector;
	const value_type _norm;
};

constexpr auto normalize(input_vector auto&& vector)
{
	return normalize_view<decltype(vector)>(NGS_PP_PERFECT_FORWARD(vector));
}



NGS_LIB_MODULE_END