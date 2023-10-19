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
struct base_contiguous_iterator : base_iterator <
	_Derived,
	std::contiguous_iterator_tag,
	_ElementType,
	_Reference,
	_Pointer,
	_DifferenceType
> {
	NGS_MPL_ENVIRON(base_contiguous_iterator);
};


NGS_BOOST_STL_INTERFACES_END
