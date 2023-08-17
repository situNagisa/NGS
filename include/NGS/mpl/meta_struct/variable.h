﻿#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

template<class _Variable>
concept CVariable = requires() {
	typename _Variable::element_type;
	{ _Variable::element_count } -> std::convertible_to<size_t>;
	{ _Variable::element_size } -> std::convertible_to<size_t>;
	{ _Variable::size } -> std::convertible_to<size_t>;
};

NGS_mfunction(variable_trait, CVariable _Variable) {
	using view_type = std::span<typename _Variable::element_type, _Variable::element_count>;
	using container_type = std::array<typename _Variable::element_type, _Variable::element_count>;
};

NGS_mfunction(variable, class  _Type, ccpt::UInt _Count) {
	NGS_mcst_t element_type = _Type;
	NGS_mcst size_t element_count = _Count::value;
	NGS_mcst size_t element_size = sizeof(element_type);
	NGS_mcst size_t size = element_count * element_size;
};

struct NGS_API variable_d {
	size_t count;
	size_t size;
	size_t offset;
};

template<class  _Type, size_t _Count = 1>
using variable_c = variable<_Type, ccpt::uint_<_Count>>;

template<class  _Type, size_t _Count = 1>
using var_ = variable_c<_Type, _Count>;

NGS_CCPT_VERIFY(CVariable, var_<int, 10>);

NGS_MPL_END
