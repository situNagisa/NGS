#pragma once

#include "./input_or_output.h"

NGS_STL_ITERATOR_BEGIN
/**
 * \brief
 * \tparam _Derived
 * \tparam _ValueType
 * \tparam _Difference
*/
template<
	class _Derived,
	class _ValueType,
	class _Reference = _ValueType&,
	class _Difference = std::ptrdiff_t
>
struct input : input_or_output<_Derived, _Difference>
{
	NGS_MPL_ENVIRON(input);
public:
	NGS_MPL_INHERIT_TYPE(iterator_type, base_type);
	using iterator_category = std::input_iterator_tag;
	using value_type = _ValueType;
	using reference = _Reference;

	using base_type::base_type;

	//constexpr type_traits::is_same_naked<value_type> auto operator*()const;
};

NGS_STL_ITERATOR_END