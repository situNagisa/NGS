#pragma once

#include "../defined.h"

NGS_BOOST_STL_INTERFACES_BEGIN

template<
	class  _Derived, 
	class _Tag, 
	class  _ElementType,
	class _Reference = _ElementType&,
	class _Pointer = _ElementType*,
	class _DifferenceType = std::ptrdiff_t
>
struct NGS_API base_iterator : boost::stl_interfaces::iterator_interface <
	_Derived,_Tag,_ElementType,_Reference,_Pointer,_DifferenceType> 
{
protected:
	using self_type = base_iterator;
public:
	using iterator_type = _Derived;

public:
	constexpr iterator_type& _derived() noexcept {
		return static_cast<iterator_type&>(*this);
	}
	constexpr const iterator_type& _derived() const noexcept {
		return static_cast<const iterator_type&>(*this);
	}
};


NGS_BOOST_STL_INTERFACES_END
