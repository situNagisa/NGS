#pragma once

#include "../param.h"
#include "./concept.h"
#include "./unpack.h"
#include "./size.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace _detail
{
	template<size_t... _Index>
	constexpr decltype(auto) replace_impl(is_param auto&& param, is_packer auto&& packer, std::index_sequence<_Index...>)
	{
		return NGS_FUNCTIONAL_PARAM_NS::forward_replace(NGS_PP_PERFECT_FORWARD(param), NGS_LIB_MODULE_NAME::unpack<_Index>(NGS_PP_PERFECT_FORWARD(packer))...);
	}

}


constexpr decltype(auto) replace(is_param auto&& param, is_packer auto&& packer)
{
	return _detail::replace_impl(NGS_PP_PERFECT_FORWARD(param), NGS_PP_PERFECT_FORWARD(packer), std::make_index_sequence<packer_size<decltype(packer)>>());
}

NGS_LIB_MODULE_END