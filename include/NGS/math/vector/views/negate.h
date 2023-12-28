#pragma once

#include "../extent.h"
#include "../norm.h"
#include "../param_trait.h"
#include "../iterator.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<input_vector _V>
struct negate_view : basic_vector, ::std::ranges::view_base, ::std::ranges::view_interface<negate_view<_V>>
{
	using trait_type = param_trait<_V>;
	constexpr static auto dereference(index_t index, typename trait_type::const_pointer vector)
	{
		return -NGS_LIB_NAME::random_access(*vector, index);
	}
	using value_type = type_traits::object_t<decltype(dereference(0, nullptr))>;
	using iterator = vector_iterator<const value_type, dereference, typename trait_type::const_pointer>;
	constexpr static auto extent = extent_v<typename trait_type::type>;

	constexpr explicit(false) negate_view(typename trait_type::param vector)
		: _vector(&vector)
	{}

	constexpr auto begin()const { return iterator(0, _vector); }
	constexpr auto end()const { return iterator(::std::ranges::size(*_vector), _vector); }

	NGS_EXTERN_STL_RANGE_INPUT_ITERATOR();
public:
	typename trait_type::const_pointer _vector;
};

constexpr auto negate(input_vector auto&& vector)
{
	return negate_view<decltype(vector)>(NGS_PP_PERFECT_FORWARD(vector));
}

NGS_LIB_MODULE_END
NGS_LIB_BEGIN

constexpr auto operator-(input_vector auto&& vector) requires tag_vector<decltype(vector)>&& scalar_vector<decltype(vector)>
{
	return NGS_LIB_MODULE_NAME::negate(NGS_PP_PERFECT_FORWARD(vector));
}

NGS_LIB_END