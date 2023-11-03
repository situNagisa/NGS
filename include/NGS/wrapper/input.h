#pragma once

#include "./defined.h"

NGS_WRAPPER_BEGIN
template<auto _InputCallback, class _Args = typename type_traits::function_traits<decltype(_InputCallback)>::args_type, class = std::make_index_sequence<std::tuple_size_v<_Args>>>
struct input_wrapper_view;

template<auto _InputCallback, class _Args, size_t... _Index>
struct input_wrapper_view<_InputCallback, _Args, std::index_sequence<_Index...>>
{
protected:
	using self_type = input_wrapper_view;
public:
	constexpr static auto input_callback = _InputCallback;
	using args_type = _Args;

	constexpr input_wrapper_view(args_type* args = nullptr) : _args(args) {}

	constexpr decltype(auto) get() const
	{
		return std::apply(input_callback, *_args);
	}

	constexpr void reset(args_type& args)
	{
		_args = &args;
	}

	constexpr operator decltype(auto)()const{ return get(); }
private:
	args_type* _args = nullptr;
};

template<auto _InputCallback, class _Args = typename type_traits::function_traits<decltype(_InputCallback)>::args_type>
struct input_wrapper : input_wrapper_view<_InputCallback, _Args>
{
	NGS_MPL_ENVIRON(input_wrapper);
public:
	NGS_MPL_INHERIT_TYPE(args_type, base_type);
public:
	using base_type::base_type;
	constexpr input_wrapper(auto&&... args) requires std::constructible_from<args_type, decltype(args)...>
		: base_type(nullptr)
		, _args(NGS_PP_PERFECT_FORWARD(args)...)
	{
		base_type::reset(_args);
	}

private:
	args_type _args;
};

template<auto _InputCallback, class... _Args>
	requires std::constructible_from<input_wrapper<_InputCallback, std::tuple<_Args...>>, _Args...>
constexpr decltype(auto) make_input_wrapper(_Args&&... args)
{
	return input_wrapper<_InputCallback, std::tuple<_Args...>>(NGS_PP_PERFECT_FORWARD(args)...);
}

NGS_WRAPPER_END