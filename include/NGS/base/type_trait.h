#pragma  once

#include "NGS/base/STL.h"
#include "NGS/base/defined.h"

NGS_BEGIN

NGS_TYPE_TRAIT

//template<class T, T val>
//struct INT_CST
//{
//    static NGS_CONSTEXPR T value = val;
//
//    using value_type = T;
//    using type = INT_CST;
//
//    NGS_CONSTEXPR operator value_type()const noexcept {
//        return value;
//    }
//
//    NGS_CONSTEXPR value_type operator()()const noexcept {
//        return value;
//    }
//};
//
//template<bool val>
//using BOOL_CST = INT_CST<bool, val>;
//using TRUE_CST = BOOL_CST<TRUE>;
//using FALSE_CST = BOOL_CST<FALSE>;
//
//NGS_EXPORT
//template<class, class>
//NGS_INL_CSTEXPR const bool IsSame = FALSE;
//NGS_EXPORT
//template<class T>
//NGS_INL_CSTEXPR const bool IsSame<T, T> = TRUE;
//
//template<class T1, class T2>
//struct _IsSame : BOOL_CST < IsSame<T1, T2>> {};
//
//
//template<class T>
//struct Remove_cv {
//    using type = T;
//};
//template<class T>
//struct Remove_cv<const T> {
//    using type = T;
//};
//template<class T>
//struct Remove_cv<volatile T> {
//    using type = T;
//};
//template<class T>
//struct Remove_cv<const volatile T> {
//    using type = T;
//};
//
//NGS_EXPORT
//template<class T>
//using Remove_cv_t = Remove_cv<T>::type;
//
//condition:true
template<bool First_value, class First, class... Rest>
struct _Disjuction {
	using type = First;
};
//condition:false
template<class First, class Next, class... Rest>
struct _Disjuction<false, First, Next, Rest...> {
	using type = typename _Disjuction<Next::value, Next, Rest...>::type;
};

template<class... Types>
struct Disjuction :std::integral_constant<bool, false> {};
template<class First, class... Types>
struct Disjuction<First, Types...> :_Disjuction<First::value, First, Types...>::type {};

template<class...Traits>
constexpr bool Disjuction_v = Disjuction<Traits...>::value;

//
//NGS_EXPORT
//template<class T>
//NGS_INL_CSTEXPR bool IsINT = IsAnyOf<Remove_cv_t<T>, bool, char, signed char, unsigned char,
//    wchar_t,
//#ifdef __cpp_char8_t
//    char8_t,
//#endif // __cpp_char8_t
//    char16_t, char32_t, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long>;
//
//NGS_EXPORT
//template<class T>
//NGS_INL_CSTEXPR bool IsUINT = IsAnyOf<Remove_cv_t<T>, bool, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;
//
//NGS_EXPORT
//template<class T>
//NGS_INL_CSTEXPR bool IsFLOAT = IsAnyOf<Remove_cv_t<T>, float, double, long double>;
//
//NGS_EXPORT
//template<class T>
//NGS_INL_CSTEXPR bool IsArithmetic = IsFLOAT<T> || IsINT<T>;


template<class A, class... Types>
constexpr bool is_any_of = Disjuction_v<std::is_same<A, Types>...>;


template<typename Type>
struct template_trait;

template<template<typename...>class Template, typename ...Args>
struct template_trait<Template<Args...>>
{
	template<typename...NewArgs>
	using type = Template<NewArgs...>;
	template<template<typename...>class NewTemplate>
	using apply = NewTemplate<Args...>;

	constexpr static auto size = sizeof... (Args);
};

//=======================================
//	Function
//=======================================

template<typename Fn>
struct function_trait {};

template<typename _ReturnType, typename... Args>
struct function_trait<_ReturnType(Args...)> {
	using type = _ReturnType(*)(Args...);
	using return_type = _ReturnType;

	constexpr static size_t param_num = sizeof...(Args);
};

template<typename _ReturnType, typename _Class, typename... Args>
struct function_trait<_ReturnType(_Class::*)(Args...)> {
	using type = _ReturnType(*)(_Class*, Args...);
	using return_type = _ReturnType;

	constexpr static size_t param_num = sizeof...(Args);
};

template<typename _Function>
using function_return_t = typename function_trait<_Function>::return_type;

template<typename _Function>
constexpr static size_t functino_param_num_v = function_trait<_Function>::param_num;

NGS_END
NGS_END