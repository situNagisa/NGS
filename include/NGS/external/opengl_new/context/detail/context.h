#pragma once

#include "../config.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


using context_t = GLuint;
inline constexpr context_t null_context = 0;

using context = handles::basic_handle<context_t, null_context>;
template<handles::handle_creator<context_t> auto Creator, handles::handle_deleter<context_t> auto Deleter>
using raii_context = handles::raii<context_t, Creator, Deleter, null_context>;

namespace _detail
{
	template<class T, class... Ts>
	concept context_binder = ::std::invocable<T, Ts...>;
}

template<class ContextType, _detail::context_binder<context_t> auto Binder>
struct context_machine : bases::singleton<context_machine<ContextType, Binder>>
{
	using context_type = ContextType;
	static_assert(::std::derived_from<context_type, context>);
	constexpr static auto context_bind_functor = Binder;

	void bind(const context_type& context) const
	{
		context_bind_functor(context.get_handle());
	}
};

#define NGS_EXTERNAL_OPENGL_CONTEXT_DEFINE_BASIC_CONTEXT(context_id,creator,deleter)	\
struct context_id :																		\
	NGS_NS::NGS_EXTERNAL_OPENGL_CONTEXT_NS::raii_context<creator, deleter>				\
{																						\
	NGS_PP_INJECT(context_id);															\
public:																					\
	NGS_EXTERNAL_OPENGL_CONTEXT_TYPE_AUTO();											\
																						\
	using base_type::base_type;															\
	using base_type::operator=;															\
}																						\
//

#define NGS_EXTERNAL_OPENGL_CONTEXT_DEFINE_BINDABLE_CONTEXT(context_id,creator,deleter,binder)			\
struct context_id :																						\
	NGS_NS::NGS_EXTERNAL_OPENGL_CONTEXT_NS::raii_context<creator, deleter>								\
{																										\
	NGS_PP_INJECT(context_id);																			\
public:																									\
	using machine_type = NGS_NS::NGS_EXTERNAL_OPENGL_CONTEXT_NS::context_machine<self_type, binder>;	\
	NGS_EXTERNAL_OPENGL_CONTEXT_TYPE_AUTO();															\
																										\
	using base_type::base_type;																			\
	using base_type::operator=;																			\
}																										\
//

NGS_LIB_MODULE_END