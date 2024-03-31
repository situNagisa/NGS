#pragma once

#define NGS_DECLARE_TV_DEFAULT(id,value_t,default)				\
template<class >												\
constexpr value_t id##_convert = default;						\
template<value_t>												\
struct NGS_DLL_API _##id##Convert;								\
template<value_t Value>											\
using id##_convert_t = typename _##id##Convert<Value>::type		\
//

#define NGS_DECLARE_TV(id,value_t)								\
NGS_DECLARE_TV_DEFAULT(id,value_t,{})							\
//

#define NGS_DEFINE_TV(id,value_t,type_,value)					\
template<>														\
constexpr value_t id##_convert<type_> = value;					\
template<>														\
struct NGS_DLL_API _##id##Convert<value> { using type = type_; };	\
//