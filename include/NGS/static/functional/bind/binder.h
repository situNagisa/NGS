#pragma once

#include "./trait.h"
#include "./parameter_pack.h"

NGS_FUNCTIONAL_BEGIN
namespace detail
{

template<size_t... _Index>
NGS_CONSTEXPR20 decltype(auto) call_binder(
	auto&& functor,
	stl::tuples::tuple_like auto&& cache,
	stl::tuples::tuple_like auto&& new_args,
	std::index_sequence<_Index...>)
{
	return std::invoke(NGS_PP_PERFECT_FORWARD(functor), fix_arg(std::get<_Index>(NGS_PP_PERFECT_FORWARD(cache)), NGS_PP_PERFECT_FORWARD(new_args))...);
}

}


template<class _FunctionType, class... _Args>
struct binder
{
	using type_category = binder_tag;
	using function_type = _FunctionType;
	using args_type = parameter_pack<_Args...>;
private:
	using function_storage_type = std::decay_t<function_type>;
	using args_storage_type = args_type;// parameter_pack<std::decay_t<_Args>...>;
public:
	constexpr explicit binder(auto&& function, auto&&... args) requires requires{ function_storage_type(NGS_PP_PERFECT_FORWARD(function)); args_storage_type(NGS_PP_PERFECT_FORWARD(args)...); }
	: _function(std::forward<function_type>(function))
		, _args(std::forward<_Args>(args)...)
	{}

	NGS_CONSTEXPR20 decltype(auto) operator()(auto&&... args)
	{
		return detail::call_binder(_function, _args, std::forward_as_tuple(NGS_PP_PERFECT_FORWARD(args)...));
	}
	NGS_CONSTEXPR20 decltype(auto) operator()(auto&&... args) const
	{
		return detail::call_binder(_function, _args, std::forward_as_tuple(NGS_PP_PERFECT_FORWARD(args)...));
	}

public:
	function_storage_type _function;
	args_storage_type _args;
};

#if defined(__cpp_deduction_guides)
template<class _FunctionType, class... _Args>
binder(_FunctionType&&, _Args&&...) -> binder<_FunctionType, _Args...>;
#endif


[[nodiscard]] constexpr decltype(auto) bind(auto&& function, auto&&... args)
{
	return binder<decltype(function), decltype(args)...>(std::forward<decltype(function)>(function), std::forward<decltype(args)>(args)...);
}

NGS_FUNCTIONAL_END