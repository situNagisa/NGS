#pragma once

#include "./random_access.h"

NGS_LIB_BEGIN
/**
 * \code
 * std::contiguous_iterator :
 *	std::is_lvalue_ref<reference>
 *	naked_same<value_type, std::remove_cvref_t<reference>>
 * requires:
 *	std::to_address(i) -> reference*
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
	class _Difference = std::ptrdiff_t
>
struct contiguous : random_access<_Derived, _ValueType, _ValueType&, _Difference>
{
	NGS_MPL_ENVIRON(contiguous);
public:
	NGS_MPL_INHERIT_TYPE(iterator_type, base_type);
	NGS_MPL_INHERIT_TYPE(difference_type, base_type);
	using iterator_category = std::contiguous_iterator_tag;

	using base_type::base_type;

	//constexpr operator value_type*() const ;
};

NGS_LIB_END