#pragma once

#include "./naked.h"
#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

namespace detail
{
	template<class>
	struct function_traits;

	template<class ResultType, class... Args>
	struct function_traits<ResultType(Args...)>
	{
		using function_type = ResultType(Args...);
		using result_type = ResultType;
		using args_type = ::std::tuple<Args...>;
	};

	template<class ResultType, class Class, class... Args>
	struct function_traits<ResultType(Class::*)(Args...)>
	{
		using function_type = ResultType(Args...);
		using result_type = ResultType;
		using args_type = ::std::tuple<Args...>;
	};

	template<class ResultType, class Class, class... Args>
	struct function_traits<ResultType(Class::*)(Args...)const>
	{
		using function_type = ResultType(Args...);
		using result_type = ResultType;
		using args_type = ::std::tuple<Args...>;
	};

	template<class Lambda>
		requires requires{ { &Lambda::operator() }; }
	struct function_traits<Lambda>
	{
		using function_type = typename function_traits<decltype(&Lambda::operator())>::function_type;
		using result_type = typename function_traits<decltype(&Lambda::operator())>::result_type;
		using args_type = typename function_traits<decltype(&Lambda::operator())>::args_type;
	};
}

template<class Functor>
using function_traits = detail::function_traits<naked_t<::std::remove_pointer_t<Functor>>>;

NGS_TYPE_TRAIT_END