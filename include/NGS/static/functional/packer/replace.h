#pragma once

#include "../param.h"
#include "./concept.h"
#include "./unpack.h"
#include "./size.h"

NGS_STATIC_FUNCTIONAL_BEGIN
namespace detail
{
template<size_t... _Index>
constexpr decltype(auto) replace_impl(is_param auto&& param, is_packer auto&& packer, std::index_sequence<_Index...>)
{
	return functional::forward_replace(NGS_PP_PERFECT_FORWARD(param), functional::unpack<_Index>(NGS_PP_PERFECT_FORWARD(packer))...);
}

}


constexpr decltype(auto) replace(is_param auto&& param, is_packer auto&& packer)
{
	return detail::replace_impl(NGS_PP_PERFECT_FORWARD(param), NGS_PP_PERFECT_FORWARD(packer), std::make_index_sequence<packer_size<decltype(packer)>>());
}

NGS_STATIC_FUNCTIONAL_END