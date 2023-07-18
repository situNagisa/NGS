#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/mpl/mpl_macro.h"
#include "NGS/base/mpl/concepts/concept.h"

NGS_BEGIN
NGS_MPL_BEGIN

NGS_mfunction(member_var, class _Type, CIntegralConstant _Num) {
	NGS_mcst_t element_type = _Type;
	NGS_mcst size_t count = _Num::value;
	NGS_mcst size_t element_size = sizeof(element_type);
	NGS_mcst size_t size = count * element_size;

	NGS_mcst_t view = std::span<element_type, count>;
	NGS_mcst_t container = std::array<element_type, count>;
	NGS_mcst_t type = view;
};

struct member_var_d {
	size_t count;
	size_t size;
	size_t offset;
};

template<class _Type, size_t _Count = 1>
using member_var_c = member_var<_Type, std::integral_constant<size_t, _Count>>;
template<class _Type, size_t _Count = 1>
using var_ = member_var_c<_Type, _Count>;

NGS_END
NGS_CONCEPT

template<class T>
concept CMetaMemberVar = requires() {
	typename T::element_type;
	{T::count} -> std::convertible_to<size_t>;
	{T::element_size} -> std::convertible_to<size_t>;
	{T::size} -> std::convertible_to<size_t>;
	typename T::type;
	typename T::view;
	typename T::container;
};

NGS_END
NGS_END
