#pragma once

#include "../base.h"

NGS_BOOST_STL_INTERFACES_BEGIN

template<
	class  _Derived,
	class  _ElementType,
	class _Reference = _ElementType&,
	class _Pointer = _ElementType*,
	class _DifferenceType = std::ptrdiff_t
>
struct base_random_access_iterator : base_iterator <
	_Derived,
	std::random_access_iterator_tag,
	_ElementType,
	_Reference,
	_Pointer,
	_DifferenceType
> {
	NGS_MPL_ENVIRON(base_random_access_iterator);
};


NGS_BOOST_STL_INTERFACES_END
