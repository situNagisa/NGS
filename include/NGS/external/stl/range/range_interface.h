#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class Derived>
struct range_interface : private ::std::ranges::view_interface<Derived>
{
	NGS_PP_INJECT_EXPLICIT(range_interface, ::std::ranges::view_interface<Derived>);
public:

	using base_type::data;
	using base_type::size;
	using base_type::empty;
	using base_type::back;
	using base_type::front;

	using base_type::operator[];
	using base_type::operator bool;

	using base_type::begin;
	using base_type::end;
#if defined(NGS_CPP_STANDARD_HAS_23)
	using base_type::cbegin;
	using base_type::cend;
#endif
};

NGS_LIB_END