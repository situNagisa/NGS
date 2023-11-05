#pragma once

#include "./forward.h"

NGS_STL_ITERATOR_BEGIN
/**
 * \code
 * std::bidirectional_iterator :
 * requires:
 *	--i
 *	i--
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
struct bidirectional : forward<_Derived, _ValueType, _Reference, _Difference>
{
	NGS_MPL_ENVIRON(bidirectional);
public:
	NGS_MPL_INHERIT_TYPE(iterator_type, base_type);
	using iterator_category = std::bidirectional_iterator_tag;

	using base_type::base_type;

	//constexpr iterator_type& operator--();
	constexpr iterator_type operator--(int)
	{
		auto tmp = base_type::_derived();
		--base_type::_derived();
		return tmp;
	}
};

NGS_STL_ITERATOR_END