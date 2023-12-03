#pragma once

#include "./input.h"

NGS_LIB_BEGIN
/**
 * \code
 * std::forward_iterator :
 *	std::sentinel_for
 *		std::semiregular
 *		weakly comparable
 *	std::incrementable
 *
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
struct forward : input<_Derived, _ValueType, _Reference, _Difference>
{
	NGS_MPL_ENVIRON(forward);
public:
	NGS_MPL_INHERIT_TYPE(iterator_type, base_type);
	using iterator_category = std::forward_iterator_tag;

	using base_type::base_type;

	//constexpr iterator_type operator++(int);
	constexpr bool operator==(const forward&) const = default;
	constexpr bool operator!=(const forward&) const = default;
	constexpr auto operator<=>(const forward&) const = default;
};

NGS_LIB_END