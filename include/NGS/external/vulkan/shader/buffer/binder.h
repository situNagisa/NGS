#pragma once

#include "./defined.h"
#include "./attribute.h"

NGS_LIB_MODULE_BEGIN

template<CAttribute... _Attributes>
struct binder
{
	using structure_type = mpl::mstruct::structure<typename _Attributes::variable_type...>;
	constexpr static size_t attribute_count = sizeof...(_Attributes);
	constexpr static ::std::array<vk::Format, attribute_count> formats = { _Attributes::format... };
};

template<class _T, class _O = type_traits::object_t<_T>>
concept CBinder = requires
{
	{ _O::attribute_count } -> ::std::convertible_to<size_t>;
	{ _O::formats } -> ::std::convertible_to<::std::array<vk::Format, _O::attribute_count>>;
		requires mpl::mstruct::CStructure<typename _O::structure_type>;
};

NGS_LIB_MODULE_END