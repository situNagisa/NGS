#pragma once

#include "./basic.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<class T, class HandleType>
concept handle_creator = ::std::invocable<T> && ::std::convertible_to<::std::invoke_result_t<T>, HandleType>;

template<class T, class HandleType>
concept handle_deleter = ::std::invocable<T, HandleType>;

template<class HandleType, handle_creator<HandleType> auto Creator, handle_deleter<HandleType> auto Deleter, HandleType Null = {} >
struct raii : basic_handle<HandleType, Null>
{
	NGS_MPL_ENVIRON(raii);
public:
	constexpr static auto create_functor = Creator;
	constexpr static auto delete_functor = Deleter;

	constexpr raii() noexcept : base_type(create_functor()) {}
	constexpr raii(self_type&&) = default;
	constexpr ~raii()
	{
		delete_functor(base_type::get_handle());
	}

	constexpr self_type& operator=(self_type&& other) noexcept
	{
		delete_functor(base_type::get_handle());
		base_type::clear_handle();
		base_type::operator=(::std::move(other));
		return *this;
	}
};

NGS_LIB_END