#pragma once

#include "./bidirectional.h"

NGS_STL_ITERATOR_BEGIN
/**
 * \code
 * std::random_access_iterator :
 *	std::sized_sentinel_for
 * requires: iterator_type i,difference_type n
 *	i += n -> iterator_type&
 *	i + n -> iterator_type
 *	i -= n -> iterator_type&
 *	i - n -> iterator_type
 *	i[n] -> value_type
 * \endcode
*/
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
struct random_access : bidirectional<_Derived, _ValueType, _Reference, _Difference>
{
	NGS_MPL_ENVIRON(random_access);
public:
	NGS_MPL_INHERIT_TYPE(iterator_type, base_type);
	NGS_MPL_INHERIT_TYPE(difference_type, base_type);
	using iterator_category = std::random_access_iterator_tag;

	using base_type::base_type;

	//constexpr iterator_type& operator+=(difference_type n);
	constexpr iterator_type operator+(difference_type n) const
	{
		iterator_type tmp = base_type::_derived();
		tmp += n;
		return tmp;
	}
	constexpr iterator_type& operator-=(difference_type n)
	{
		return base_type::_derived() += -n;
	}
	constexpr iterator_type operator-(difference_type n) const
	{
		iterator_type tmp = base_type::_derived();
		tmp -= n;
		return tmp;
	}
};

NGS_STL_ITERATOR_END