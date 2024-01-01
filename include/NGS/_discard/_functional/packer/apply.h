#pragma once

#include "./forward_as_packer.h"
#include "./replace.h"
#include "./size.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace _detail
{

	template<size_t... _Index>
	constexpr decltype(auto) apply_imp(std::index_sequence<_Index...>, auto&& callable, is_packer auto&& packer, auto&&... params)
	{
		return NGS_PP_PERFECT_FORWARD(callable)(NGS_FUNCTIONAL_PARAM_NS::forward_replace(NGS_LIB_MODULE_NAME::unpack<_Index>(NGS_PP_PERFECT_FORWARD(packer)), NGS_PP_PERFECT_FORWARD(params)...)...);
	}
}

constexpr decltype(auto) apply(auto&& callable, is_packer auto&& packer, auto&&... params)
{
	return _detail::apply_imp(std::make_index_sequence<packer_size<decltype(packer)>>(), NGS_PP_PERFECT_FORWARD(callable), NGS_PP_PERFECT_FORWARD(packer), NGS_PP_PERFECT_FORWARD(params)...);
}

NGS_LIB_MODULE_END
NGS_LIB_MODULE_EXPORT(apply);