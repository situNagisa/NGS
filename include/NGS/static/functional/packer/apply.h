#pragma once

#include "./forward_as_packer.h"
#include "./replace.h"
#include "./size.h"

NGS_STATIC_FUNCTIONAL_BEGIN
namespace detail
{

template<size_t... _Index>
constexpr decltype(auto) apply_imp(std::index_sequence<_Index...>, auto&& callable, is_packer auto&& packer, auto&&... params)
{
	return callable(functional::forward_replace(functional::unpack<_Index>(NGS_PP_PERFECT_FORWARD(packer)), NGS_PP_PERFECT_FORWARD(params)...)...);
}
}

constexpr decltype(auto) apply(auto&& callable, is_packer auto&& packer, auto&&... params)
{
	return detail::apply_imp(std::make_index_sequence<packer_size<decltype(packer)>>(), NGS_PP_PERFECT_FORWARD(callable), NGS_PP_PERFECT_FORWARD(packer), NGS_PP_PERFECT_FORWARD(params)...);
}

NGS_STATIC_FUNCTIONAL_END