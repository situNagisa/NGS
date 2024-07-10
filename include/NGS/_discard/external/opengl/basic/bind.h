#pragma once

#include "../config.h"
#include "./machine.h"
#include "./context.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace detail
{
	template<class _State>
	concept has_member = requires(_State s)
	{
		{ NGS_PP_PERFECT_FORWARD(s).bind() };
	};

	template<class _State>
	concept has_adl = requires(_State s)
	{
		{ bind(NGS_PP_PERFECT_FORWARD(s)) };
	};
}

template<class T>
concept bindable = ::std::derived_from<type_traits::naked_t<T>,context> && (detail::has_member<T> || detail::has_adl<T> || machine<state_machine_t<T>>);

namespace _detail
{
	template<class>
	inline context_t current_binding_context_impl = null_context;

	template<class T,class = typename type_traits::naked_t<T>::binding_context_type>
	auto current_binding_context() {
		return current_binding_context_impl<typename type_traits::naked_t<T>::binding_context_type>;
	}
	template<class T, class = typename type_traits::naked_t<T>::binding_context_type>
	auto current_binding_context(context_t context) {
		current_binding_context_impl<typename type_traits::naked_t<T>::binding_context_type> = context;
	}
}

inline constexpr struct
{
	constexpr decltype(auto) operator()(bindable auto&& s)const
	{
		using state_type = decltype(s);

#if defined(NGS_EXTERNAL_OPENGL_CHECK_BIND)
		auto&& context = NGS_PP_PERFECT_FORWARD(s).get_context();
		if(context == _detail::current_binding_context<state_type>())
		{
			return;
		}
		_detail::current_binding_context<state_type>(NGS_PP_PERFECT_FORWARD(context));
#endif

		if constexpr (detail::has_member<state_type>)
		{
			return NGS_PP_PERFECT_FORWARD(s).bind();
		}
		else if constexpr (detail::has_adl<state_type>)
		{
			return bind(NGS_PP_PERFECT_FORWARD(s));
		}
		else if constexpr (machine<state_machine_t<state_type>>)
		{
			typename state_machine_t<state_type>::instance().bind(NGS_PP_PERFECT_FORWARD(s));
		}
		else
		{
			static_assert(cpt::none<decltype(s)>, "bind not found");
		}
	}
}bind{};

NGS_LIB_MODULE_END

#if defined(NGS_EXTERNAL_OPENGL_CHECK_BIND)
#	define NGS_EXTERNAL_OPENGL_EXPECT_BIND(bindable)																																			\
NGS_ASSERT(																																														\
	NGS_NS::NGS_EXTERNAL_NS::NGS_EXTERNAL_OPENGL_NS::NGS_EXTERNAL_OPENGL_BASIC_NS::_detail::current_binding_context<decltype(bindable)>() == (bindable).get_context(),							\
	NGS_NS::fmt::c("the operation needs to bind the %s's context(%d) first",NGS_NS::symbols::type_name<NGS_NS::type_traits::naked_t<decltype(bindable)>>().data(), (bindable).get_context())	\
)																																																\
//
#else
#	define NGS_EXTERNAL_OPENGL_EXPECT_BIND(bindable)
#endif