#pragma once

#include "../config.h"
#include "./context.h"
#include "./machine.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace detail
{
	template<class State>
	concept has_member = requires(State s)
	{
		{ NGS_PP_PERFECT_FORWARD(s).bind() };
	};

	template<class State>
	concept has_adl = requires(State s)
	{
		{ bind(NGS_PP_PERFECT_FORWARD(s)) };
	};
}

template<class T>
concept bindable = ::std::derived_from<type_traits::naked_t<T>,context> && (detail::has_member<T> || detail::has_adl<T> || machine<state_machine_t<T>>);


#if defined(NGS_EXTERNAL_OPENGL_CONTEXT_CHECK_BIND)


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
	//remove adl
	void bind_(bindable auto&& s)
	{
		_detail::current_binding_context<decltype(s)>(NGS_PP_PERFECT_FORWARD(s).get_handle());
	}

	bool is_binding(bindable auto&& s)
	{
		auto&& context = NGS_PP_PERFECT_FORWARD(s).get_handle();
		return context == _detail::current_binding_context<decltype(s)>();
	}

	void unbind(bindable auto&& s)
	{
		NGS_ASSERT(_detail::is_binding<decltype(s)>(NGS_PP_PERFECT_FORWARD(s)), "unbind error");
		_detail::current_binding_context<decltype(s)>(null_context);
	}
}
using _detail::is_binding;
using _detail::unbind;


#endif

inline constexpr struct
{
	constexpr decltype(auto) operator()(bindable auto&& s)const
	{
		using state_type = decltype(s);

#if defined(NGS_EXTERNAL_OPENGL_CONTEXT_CHECK_BIND)
		if(_detail::is_binding(NGS_PP_PERFECT_FORWARD(s)))
			return;
		
		_detail::bind_(NGS_PP_PERFECT_FORWARD(s));
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

#if defined(NGS_EXTERNAL_OPENGL_CONTEXT_CHECK_BIND)
#	define NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(bindable)																	\
NGS_ASSERT(																														\
	NGS_NS::NGS_EXTERNAL_OPENGL_CONTEXT_NS::details::is_binding(bindable),														\
	NGS_NS::fmt::c(																												\
		"the operation needs to bind the %s's context(%d) first",																\
		NGS_NS::symbols::field_symbol_name<NGS_NS::type_traits::naked_t<decltype(bindable)>>().data(), (bindable).get_handle()	\
	)																															\
)																																\
//
#else
#	define NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(bindable)
#endif