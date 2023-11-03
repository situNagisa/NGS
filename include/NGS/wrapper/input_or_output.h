#pragma once

#include "./input.h"
#include "./output.h"

NGS_WRAPPER_BEGIN

template<auto _InputCallback, auto _OutputCallback, class _Args = typename type_traits::function_traits<decltype(_InputCallback)>::args_type>
struct input_or_output_wrapper_view : input_wrapper_view<_InputCallback, _Args>, output_wrapper_view<_OutputCallback, _Args>
{
protected:
	using self_type = input_or_output_wrapper_view;
private:
	using base_input_type = input_wrapper_view<_InputCallback, _Args>;
	using base_output_type = output_wrapper_view<_OutputCallback, _Args>;
public:
	using args_type = _Args;
	NGS_MPL_INHERIT_VALUE(input_callback, base_input_type);
	NGS_MPL_INHERIT_VALUE(output_callback, base_output_type);

	constexpr input_or_output_wrapper_view(args_type* args = nullptr)
		: base_input_type(args)
		, base_output_type(args)
	{}

	constexpr void reset(args_type& args)
	{
		base_input_type::reset(args);
		base_output_type::reset(args);
	}

	using base_output_type::operator=;
};

template<auto _InputCallback, auto _OutputCallback, class _Args = typename type_traits::function_traits<decltype(_InputCallback)>::args_type>
struct input_or_output_wrapper : input_or_output_wrapper_view<_InputCallback, _OutputCallback, _Args>
{
	NGS_MPL_ENVIRON(input_or_output_wrapper);
public:
	using args_type = _Args;

	constexpr input_or_output_wrapper(auto&&... args) requires std::constructible_from<args_type, decltype(args)...>
		: base_type(nullptr)
		, _args(NGS_PP_PERFECT_FORWARD(args)...)
	{
		base_type::reset(_args);
	}

	using base_type::operator=;
private:
	args_type _args;
};

template<auto _InputCallback, auto _OutputCallback, class... _Args>
	requires std::constructible_from<input_or_output_wrapper<_InputCallback, _OutputCallback, std::tuple<_Args...>>, _Args...>
constexpr decltype(auto) make_input_or_output_wrapper(_Args&&... args)
{
	return input_or_output_wrapper<_InputCallback, _OutputCallback, std::tuple<_Args...>>(NGS_PP_PERFECT_FORWARD(args)...);
}

NGS_WRAPPER_END
