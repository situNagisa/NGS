#pragma once

#include "./defined.h"
#include "./access.h"

NGS_MATH_LA_VECTOR_INTERFACE_BEGIN
constexpr void assign() {}
NGS_MATH_LA_VECTOR_INTERFACE_END
NGS_MATH_LA_VECTOR_ADAPTER_BEGIN
namespace detail
{
	template<class _L, class _R>
	constexpr functor_choice assign_choice()
	{
		using value_type = _R;
		if constexpr (requires(_L target, traits::vectors::index_t index, value_type value) { interfaces::vectors::assign(NGS_PP_PERFECT_FORWARD(target), index, NGS_PP_PERFECT_FORWARD(value)); })
		{
			return functor_choice::interface;
		}
		else if constexpr (requires(_L target, traits::vectors::index_t index, value_type value) { target.assign(index, NGS_PP_PERFECT_FORWARD(value)); })
		{
			return functor_choice::member;
		}
		else if constexpr (requires(_L target, traits::vectors::index_t index, value_type value) { requires std::assignable_from<decltype(access(NGS_PP_PERFECT_FORWARD(target), index)), value_type>; })
		{
			return functor_choice::other;
		}
		else
		{
			return functor_choice::none;
		}
	}

}

/**
 * \brief 可赋值
 *
 * \tparam _L 左边
 * \tparam _R 右边
 *
 * \note 当用户重载了\code interfaces::vectors::assign \endcode 函数时
 * \note 当\code _L::assign \endcode 函数存在时,且能接受类型为\code index_t \endcode 和\code _R\endcode 的参数时
 * \note 当满足\code std::assignable_from<decltype(access(_L,index_t)),_R \endcode
 *
 * \return 当满足`note`所述条件时,返回`true`,否则返回`false`
*/
template<class _L, class _R = _L>
concept assignable = detail::assign_choice<_L, _R>() != functor_choice::none;

/**
 * \brief 赋值
 *
 * \concept assignable
 *
 * \param target 被赋值的目标，须满足概念\code assignable \endcode
 * \param index  被赋值的下标
 * \param value  赋值的值
 *
 * \return 取决于所依赖的函数
 *
 * \code
 * vector3i v{1,2,3};
 * assign(v,0,2);
 * \endcode
 *
 */
inline constexpr struct
{

	constexpr decltype(auto) operator()(auto&& target, traits::vectors::index_t index, auto&& value) const
		requires assignable<decltype(target), decltype(value)>
	{
		constexpr auto choice = detail::assign_choice<decltype(target), decltype(value)>();
		if constexpr (choice == functor_choice::interface)
		{
			return interfaces::vectors::assign(NGS_PP_PERFECT_FORWARD(target), index, NGS_PP_PERFECT_FORWARD(value));
		}
		else if constexpr (choice == functor_choice::member)
		{
			return target.assign(index, value);
		}
		else if constexpr (choice == functor_choice::other)
		{
			return access(NGS_PP_PERFECT_FORWARD(target), index) = NGS_PP_PERFECT_FORWARD(value);
		}
		else
		{
			static_assert(choice != functor_choice::none);
		}
	}
} assign;

NGS_MATH_LA_VECTOR_ADAPTER_END
