#pragma once

#include "./defined.h"

NGS_WRAPPER_BEGIN
namespace detail
{
template<class _Function, class _Args = typename type_traits::function_traits<_Function>::args_type, class = std::make_index_sequence<std::tuple_size_v<_Args> -1>>
struct get_callback_args;

template<class _Function, class _Args, size_t... _Index>
struct get_callback_args<_Function, _Args, std::index_sequence<_Index...>>
{
	using type = std::tuple<std::tuple_element_t<_Index, _Args>...>;
};

template<class _Function>
using get_callback_args_t = typename get_callback_args<_Function>::type;

}

template<auto _OutputCallback, class _Args = detail::get_callback_args_t<decltype(_OutputCallback)>, class = std::make_index_sequence<std::tuple_size_v<_Args>>>
struct output_wrapper_view;

template<auto _OutputCallback, class _Args, size_t... _Index>
struct output_wrapper_view<_OutputCallback, _Args, std::index_sequence<_Index...>>
{
protected:
	using self_type = output_wrapper_view;
public:
	constexpr static auto output_callback = _OutputCallback;
	using args_type = _Args;

	constexpr output_wrapper_view() = default;
	constexpr output_wrapper_view(args_type* args) : _args(args) {}

	constexpr void reset(args_type& args)
	{
		_args = &args;
	}

	constexpr decltype(auto) set(auto&& value) const
		requires std::is_invocable_v<decltype(output_callback), const std::tuple_element_t<_Index, args_type>..., decltype(value)>
	{
		return output_callback(std::get<_Index>(*_args)..., NGS_PP_PERFECT_FORWARD(value));
	}

	constexpr decltype(auto) operator=(auto&& value) const
		requires std::is_invocable_v<decltype(output_callback), const std::tuple_element_t<_Index, args_type>..., decltype(value)>
	{
		return set(NGS_PP_PERFECT_FORWARD(value));
	}

private:
	args_type* _args{};
};

template<auto _InputCallback, class _Args = typename type_traits::function_traits<decltype(_InputCallback)>::args_type>
struct output_wrapper : output_wrapper_view<_InputCallback, _Args>
{
	NGS_MPL_ENVIRON(output_wrapper);
public:
	NGS_MPL_INHERIT_TYPE(args_type, base_type);
public:
	using base_type::base_type;
	constexpr output_wrapper(auto&&... args)
		requires std::constructible_from<args_type, decltype(args)...>
	: base_type(nullptr)
		, _args(NGS_PP_PERFECT_FORWARD(args)...)
	{
		base_type::reset(_args);
	}

	using base_type::operator=;

private:
	args_type _args;
};

template<auto _OutputCallback, class... _Args>
	requires std::constructible_from<output_wrapper<_OutputCallback, std::tuple<_Args...>>, _Args...>
constexpr decltype(auto) make_output_wrapper(_Args&&... args)
{
	return output_wrapper<_OutputCallback, std::tuple<_Args...>>(NGS_PP_PERFECT_FORWARD(args)...);
}


NGS_WRAPPER_END