#pragma once

#include "./concept.h"

NGS_STATIC_FUNCTIONAL_BEGIN
/**
 * \brief 参数变换
 * \note 用于参数变换，例如将参数转发到另一个函数，或者将参数转发到另一个函数的参数中
 * \note 可通过继承概念`is_param`来重载该函数，添加自定义的行为
 * \param param
 * \param params
 * \return decltype(auto)
*/
constexpr decltype(auto) forward_replace(is_param auto&& param, auto&&... params)
{
	return NGS_PP_PERFECT_FORWARD(param);
}

NGS_STATIC_FUNCTIONAL_END