#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

/// 
/// @param identifier 
/// @param statement[optional] 
#define NGS_TCEA_TRAIT_DEFAULT(...) BOOST_PP_OVERLOAD(NGS_TCEA_TRAIT_DEFAULT_O_, __VA_ARGS__)(__VA_ARGS__)
#define NGS_TCEA_TRAIT_DEFAULT_O_2(identifier, statement) template<class T> struct identifier { statement }
#define NGS_TCEA_TRAIT_DEFAULT_O_1(identifier) NGS_TCEA_TRAIT_DEFAULT_O_2(identifier, )

#define NGS_TCEA_TRAIT_DEFAULT_TYPE(identifier, default_type) NGS_TCEA_TRAIT_DEFAULT(identifier, using type = default_type;)
#define NGS_TCEA_TRAIT_DEFAULT_VALUE(identifier, default_value) NGS_TCEA_TRAIT_DEFAULT(identifier, constexpr static auto value = default_value;)

#define NGS_TCEA_TRAIT_ALIAS_T(identifier) template<class T> using identifier##_t = typename identifier<T>::type
#define NGS_TCEA_TRAIT_ALIAS_V(identifier) template<class T> inline constexpr auto identifier##_v = identifier<T>::value

#define NGS_TCEA_TRAIT_HAS_SYMBOL(identifier, symbol_name, project, tv)	\
template<class T>														\
	requires requires { project(T)::symbol_name; }						\
struct identifier<T> { tv = project(T)::symbol_name; }					\
//

#define NGS_TCEA_TRAIT_PRIVATE_HAS_TYPE_PROJECT(type) typename type
#define NGS_TCEA_TRAIT_PRIVATE_HAS_TYPE_PROJECT_OBJECT(type) typename ::std::remove_reference_t<type>
#define NGS_TCEA_TRAIT_HAS_TYPE_PROJECT(identifier, type_name, project) NGS_TCEA_TRAIT_HAS_SYMBOL(identifier, type_name, project, using type)
#define NGS_TCEA_TRAIT_HAS_TYPE(identifier, type_name) NGS_TCEA_TRAIT_HAS_TYPE_PROJECT(identifier, type_name, NGS_TCEA_TRAIT_PRIVATE_HAS_TYPE_PROJECT)
#define NGS_TCEA_TRAIT_HAS_TYPE_OBJECT(identifier, type_name) NGS_TCEA_TRAIT_HAS_TYPE_PROJECT(identifier, type_name, NGS_TCEA_TRAIT_PRIVATE_HAS_TYPE_PROJECT_OBJECT)

#define NGS_TCEA_TRAIT_PRIVATE_HAS_VALUE_PROJECT(type) type
#define NGS_TCEA_TRAIT_PRIVATE_HAS_VALUE_PROJECT_OBJECT(type) ::std::remove_reference_t<type>
#define NGS_TCEA_TRAIT_HAS_VALUE_PROJECT(identifier, value_name, project) NGS_TCEA_TRAIT_HAS_SYMBOL(identifier, value_name, project, constexpr static auto value)
#define NGS_TCEA_TRAIT_HAS_VALUE(identifier, value_name) NGS_TCEA_TRAIT_HAS_VALUE_PROJECT(identifier, value_name, NGS_TCEA_TRAIT_PRIVATE_HAS_VALUE_PROJECT_OBJECT)
#define NGS_TCEA_TRAIT_HAS_VALUE_OBJECT(identifier, value_name) NGS_TCEA_TRAIT_HAS_VALUE_PROJECT(identifier, value_name, NGS_TCEA_TRAIT_PRIVATE_HAS_VALUE_PROJECT_OBJECT)

#define NGS_TCEA_PRIVATE_DECLARE(z, index, args) BOOST_PP_TUPLE_ELEM(index, args) ngs_tcea_arg_##index
#define NGS_TCEA_PRIVATE_ARG(z, index, args) NGS_PP_PERFECT_FORWARD(ngs_tcea_arg_##index)

#define NGS_TCEA_PRIVATE_INVOCABLE_MEMBER(target, function, parameters)												\
requires(target t, BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(parameters),NGS_TCEA_PRIVATE_DECLARE, parameters))				\
{																													\
	{ NGS_PP_PERFECT_FORWARD(t).function(BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(parameters), NGS_TCEA_PRIVATE_ARG, )) };	\
}																													\
//
#define NGS_TCEA_PRIVATE_INVOCABLE_ADL(target, function, parameters)												\
requires(target t, BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(parameters), NGS_TCEA_PRIVATE_DECLARE, parameters))			\
{																													\
	{ function(NGS_PP_PERFECT_FORWARD(t), BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(parameters), NGS_TCEA_PRIVATE_ARG, )) };\
}																													\
//

#define NGS_TCEA_PRIVATE_CONCEPT(z, index, args) BOOST_PP_TUPLE_ELEM(index, args) auto&& arg_##index
#define NGS_TCEA_PRIVATE_CPO_ARG_TYPE(z, index, args) decltype(arg_##index)
#define NGS_TCEA_PRIVATE_CPO_ARG(z, index, args) NGS_PP_PERFECT_FORWARD(arg_##index)

/// 
/// @param function 
/// @param concepts tuple, size can't be 0
#define NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(...) BOOST_PP_OVERLOAD(NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT_O_, __VA_ARGS__)(__VA_ARGS__)
#define NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT_O_1(function)								\
namespace detail_##function																\
{																						\
	template<class T>																	\
	concept has_member = requires(T t){ { NGS_PP_PERFECT_FORWARD(t).function() }; };	\
	template<class T>																	\
	concept has_adl = requires(T t){ { function(NGS_PP_PERFECT_FORWARD(t)) }; };		\
	template<class T>																	\
	concept invocable =	has_member<T> || has_adl<T>;									\
}																						\
inline constexpr struct																	\
{																						\
	template<class T>																	\
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(				\
		T&& target																		\
		) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST											\
		requires detail_##function::invocable<decltype(target)>							\
	{																					\
		if constexpr (detail_##function::has_member<decltype(target)>)					\
		{																				\
			return NGS_PP_PERFECT_FORWARD(target).function();							\
		}																				\
		else if constexpr (detail_##function::has_adl<decltype(target)>)				\
		{																				\
			return function(NGS_PP_PERFECT_FORWARD(target));							\
		}																				\
	}																					\
}function{}																				\
//

#define NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT_O_2(function, concepts)																					\
namespace detail_##function																															\
{																																					\
	template<class T, BOOST_PP_ENUM_PARAMS(BOOST_PP_TUPLE_SIZE(concepts), class T)>																	\
	concept has_member = NGS_TCEA_PRIVATE_INVOCABLE_MEMBER(T, function, (BOOST_PP_ENUM_PARAMS(BOOST_PP_TUPLE_SIZE(concepts), T)));					\
	template<class T, BOOST_PP_ENUM_PARAMS(BOOST_PP_TUPLE_SIZE(concepts), class T)>																	\
	concept has_adl = NGS_TCEA_PRIVATE_INVOCABLE_ADL(T, function, (BOOST_PP_ENUM_PARAMS(BOOST_PP_TUPLE_SIZE(concepts), T)));						\
	template<class T, BOOST_PP_ENUM_PARAMS(BOOST_PP_TUPLE_SIZE(concepts), class T)>																	\
	concept invocable = 																															\
		has_member<T, BOOST_PP_ENUM_PARAMS(BOOST_PP_TUPLE_SIZE(concepts), T)>																		\
		|| has_adl<T, BOOST_PP_ENUM_PARAMS(BOOST_PP_TUPLE_SIZE(concepts), T)>;																		\
}																																					\
inline constexpr struct																																\
{																																					\
	template<class T>																																\
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(																			\
		T&& target, 																																\
		BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(concepts), NGS_TCEA_PRIVATE_CONCEPT, concepts)															\
		) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST																										\
		requires detail_##function::invocable<decltype(target), BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(concepts), NGS_TCEA_PRIVATE_CPO_ARG_TYPE, )>		\
	{																																				\
		if constexpr (detail_##function::has_member<decltype(target), BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(concepts), NGS_TCEA_PRIVATE_CPO_ARG_TYPE, )>)\
		{																																			\
			return NGS_PP_PERFECT_FORWARD(target).function(BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(concepts), NGS_TCEA_PRIVATE_CPO_ARG, ));				\
		}																																			\
		else if constexpr (detail_##function::has_adl<decltype(target), BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(concepts), NGS_TCEA_PRIVATE_CPO_ARG_TYPE, )>)\
		{																																			\
			return function(NGS_PP_PERFECT_FORWARD(target), BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(concepts), NGS_TCEA_PRIVATE_CPO_ARG, ));				\
		}																																			\
	}																																				\
}function{}																																			\
//

NGS_LIB_MODULE_END