#pragma once

#include "../concept.h"

NGS_MATH_MATRIX_FUNCTOR_BEGIN
/**
 * \brief 获取闭包类型
 * \tparam _T matrix容器
 * \note 需要注意的是，当_T不为左值引用时，闭包类型为_T，此时会发生大量复制，降低效率，所以请尽量使用左值引用
*/
template<storage _T>
struct closure<_T>
{
	using type = std::conditional_t<
		std::is_lvalue_reference_v<_T>,
		std::add_lvalue_reference_t<_T>,
		std::remove_reference_t<_T>
	>;
};

NGS_MATH_MATRIX_FUNCTOR_END
