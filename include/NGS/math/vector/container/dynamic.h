#pragma once

#include "./vector.h"

NGS_LIB_MODULE_BEGIN

template<class _T>
struct vector<_T, dynamic_extent>
	: ::std::vector<_T>
	, allow_adl_operator, allow_adl_io
	, NGS_MATH_VECTOR_TAG_NS::tag<NGS_MATH_VECTOR_TAG_NS::vector>
{
	NGS_MPL_ENVIRON_BEGIN(vector);
	using base_type = ::std::vector<_T>;
public:
	using base_type::base_type;
	using base_type::operator=;

	constexpr explicit(false) vector(auto&& other)requires assignable_from<self_type, decltype(other)>
		: base_type(::std::ranges::size(NGS_PP_PERFECT_FORWARD(other)))
	{
		NGS_MATH_VECTOR_OPERATE_NS::assign(*this, NGS_PP_PERFECT_FORWARD(other));
	}
	constexpr self_type& operator=(auto&& other)
		requires assignable_from<self_type, decltype(other)>
	{
		base_type::reserve(::std::ranges::size(NGS_PP_PERFECT_FORWARD(other)));
		NGS_MATH_VECTOR_OPERATE_NS::assign(*this, NGS_PP_PERFECT_FORWARD(other));

		return *this;
	}
};

NGS_LIB_MODULE_END