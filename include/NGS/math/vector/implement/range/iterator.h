#pragma once

#include "./wrapper.h"

NGS_MATH_VECTOR_BEGIN

namespace detail
{

template<functor::accessible _Type>
struct vector_expression_iterator :
	nboost::stl_interfaces::base_random_access_iterator<
	vector_expression_iterator<_Type>,
	value_wrapper<_Type>
	>
{
	NGS_MPL_ENVIRON2(vector_expression_iterator,
		nboost::stl_interfaces::base_random_access_iterator<
		vector_expression_iterator<_Type>,
		value_wrapper<_Type>
		>);
public:
	NGS_MPL_INHERIT_TYPE(iterator_type, base_type);
	NGS_MPL_INHERIT_TYPE(value_type, base_type);
	NGS_MPL_INHERIT_TYPE(reference, base_type);
	NGS_MPL_INHERIT_TYPE(pointer, base_type);
	NGS_MPL_INHERIT_TYPE(difference_type, base_type);

	using range_type = _Type;
public:
	using base_type::base_type;
	constexpr vector_expression_iterator(range_type* range, size_t index)
		: _range(range)
		, _index(index)
	{}
	constexpr vector_expression_iterator() = default;

	constexpr iterator_type& operator+=(difference_type n) {
		_index += n;
		return base_type::_derived();
	}
	constexpr difference_type operator-(self_type other)const { return other._index - _index; }

	constexpr decltype(auto) operator*()const {
		return value_type(_range, _index);
	}
private:
	range_type* _range = nullptr;
	size_t _index = 0;
};
}

NGS_MATH_VECTOR_END