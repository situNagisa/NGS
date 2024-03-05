#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<
	class Derived, 
	class Tag, 
	class ElementType,
	class Reference = ElementType&,
	class Pointer = ElementType*,
	class DifferenceType = std::ptrdiff_t
>
struct NGS_DLL_API basic_interface : boost::stl_interfaces::iterator_interface <Derived,Tag,ElementType,Reference,Pointer,DifferenceType>
{
	NGS_MPL_ENVIRON_BEGIN(basic_interface);
public:
	using iterator_type = Derived;

public:
	constexpr auto&& _derived() noexcept { return static_cast<iterator_type&>(*this); }
	constexpr auto&& _derived() const noexcept { return static_cast<const iterator_type&>(*this); }
};


NGS_LIB_MODULE_END
