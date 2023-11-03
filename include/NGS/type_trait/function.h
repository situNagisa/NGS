#pragma once

#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class>
struct function_traits;

template<class _ResultType, class... _Args>
struct function_traits<_ResultType(*)(_Args...)>
{
	using function_type = _ResultType(_Args...);
	using result_type = _ResultType;
	using args_type = std::tuple<_Args...>;
};

template<class _ResultType, class... _Args>
struct function_traits<_ResultType(_Args...)>
{
	using function_type = _ResultType(_Args...);
	using result_type = _ResultType;
	using args_type = std::tuple<_Args...>;
};

template<class _ResultType, class _Class, class... _Args>
struct function_traits<_ResultType(_Class::*)(_Args...)>
{
	using function_type = _ResultType(_Args...);
	using result_type = _ResultType;
	using args_type = std::tuple<_Args...>;
};

template<class _ResultType, class _Class, class... _Args>
struct function_traits<_ResultType(_Class::*)(_Args...)const>
{
	using function_type = _ResultType(_Args...);
	using result_type = _ResultType;
	using args_type = std::tuple<_Args...>;
};

template<class _Lambda>
	requires requires{ { &_Lambda::operator() }; }
struct function_traits<_Lambda>
{
	using function_type = typename function_traits<decltype(&_Lambda::operator())>::function_type;
	using result_type = typename function_traits<decltype(&_Lambda::operator())>::result_type;
	using args_type = typename function_traits<decltype(&_Lambda::operator())>::args_type;
};

NGS_TYPE_TRAIT_END