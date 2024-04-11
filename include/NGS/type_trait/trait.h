#pragma once

#include "./object.h"
#include "./defined.h"

#define NGS_TYPE_TRAIT_TYPE(id, symbol)											\
template<class> struct id {};														\
template<class T> requires requires{ typename type_traits::object_t<T>::symbol; }	\
struct id<T>																		\
{																					\
	using type = typename type_traits::object_t<T>::symbol;							\
};																					\
template<class T> requires requires{ typename id<T>::type; }						\
using id##_t = typename id<T>::type;												\
//

#define NGS_TYPE_TRAIT_VALUE(id, symbol)													\
template<class> struct id##_trait {};														\
template<class T> requires requires{ { type_traits::object_t<T>::symbol() }; }				\
struct id##_trait<T>																		\
{																							\
	static constexpr decltype(auto) value() { return type_traits::object_t<T>::symbol(); }	\
};																							\
template<class T> requires requires{ id##_trait<T>::value(); }								\
constexpr decltype(auto) id(){ return id##_trait<T>::value(); }								\
//