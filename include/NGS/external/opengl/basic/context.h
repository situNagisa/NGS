#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using context_t = GLuint;
inline constexpr context_t null_context = static_cast<context_t>(0);

struct context : bases::delete_copy
{
	NGS_MPL_ENVIRON_BEGIN(context);
public:
	constexpr explicit(false) context(const context_t& context) noexcept : _context(context) {}
	constexpr context(self_type&& other)noexcept : _context(other._context)
	{
		other._context = 0;
	}
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
	constexpr ~context()
	{
		_context = 0;
	}
#endif
	constexpr self_type& operator=(self_type&& other) noexcept
	{
		if (!::std::is_constant_evaluated())
			NGS_EXPECT(_context == 0);
		_context = other._context;
		other._context = 0;
		return *this;
	}

	constexpr auto&& get_context() const noexcept { return _context; }

	constexpr void _set_context(const context_t& c) { _context = c; }
private:
	context_t _context{};
};

namespace _detail
{
	template<class T>
	concept context_creator = ::std::invocable<T> && ::std::convertible_to<::std::invoke_result_t<T>, context_t>;

	template<class T>
	concept context_deleter = ::std::invocable<T, context_t>;

	template<class T,class... Ts>
	concept context_binder = ::std::invocable<T, Ts...>;
}

template<_detail::context_creator auto Creator,_detail::context_deleter auto Deleter>
struct raii_context : context
{
	NGS_MPL_ENVIRON(raii_context);
public:
	constexpr static auto context_create_functor = Creator;
	constexpr static auto context_delete_functor = Deleter;

	raii_context() noexcept : base_type(context_create_functor()) {}
	raii_context(self_type&&) = default;
	~raii_context()
	{
		context_delete_functor(get_context());
	}

	self_type& operator=(self_type&& other) noexcept
	{
		context_delete_functor(get_context());
		_set_context(0);
		base_type::operator=(::std::move(other));
		return *this;
	}
};

template<class ContextType, _detail::context_binder<context_t> auto Binder>
struct context_machine : bases::singleton<context_machine<ContextType,Binder>>
{
	using context_type = ContextType;
	constexpr static auto context_bind_functor = Binder;

	void bind(const context_type& context) const
	{
		context_bind_functor(context.get_context());
	}
};

#define NGS_EXTERNAL_OPENGL_DEFINE_BINDABLE_CONTEXT(context_id,creator,deleter)										\
struct context_id :																									\
	NGS_NS::NGS_EXTERNAL_NS::NGS_EXTERNAL_OPENGL_NS::NGS_EXTERNAL_OPENGL_BASIC_NS::raii_context<creator, deleter>	\
{																													\
	NGS_MPL_ENVIRON(context_id);																					\
public:																												\
	NGS_EXTERNAL_OPENGL_CONTEXT_TYPE_AUTO();																		\
																													\
	using base_type::base_type;																						\
	using base_type::operator=;																						\
}																													\
//

NGS_LIB_MODULE_END