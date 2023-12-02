#pragma once

#include "../defined.h"

NGS_LIB_MODULE_BEGIN

template<class _Type>
struct attribute
{
	using variable_type = mpl::mstruct::variable<_Type>;

	constexpr static auto format = type_maps::format::value<type_maps::adapter_t<typename variable_type::storage_type>>;
};

template<class _T, class _O = type_traits::object_t<_T>>
concept CAttribute = requires
{
	{ _O::format } -> ::std::convertible_to<vk::Format>;
	requires mpl::mstruct::CVariable<typename _O::variable_type>;
};

NGS_LIB_MODULE_END