#pragma once

#include "./vector.h"

NGS_LIB_MODULE_BEGIN

template<class _T>
struct vector<_T, dynamic_extent> : ::std::vector<_T>, basic_vector
{
	NGS_MPL_ENVIRON_BEGIN(vector);
	using base_type = ::std::vector<_T>;
public:
	using base_type::base_type;
};

NGS_LIB_MODULE_END