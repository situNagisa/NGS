#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t BitSize>
struct basic_register
{
	NGS_PP_INJECT_BEGIN(basic_register);
public:
	constexpr static auto bit_size() { return BitSize; }
};

#define NGS_OS_X86_REGISTER_DERIVED_FROM(id)											\
namespace _detail																		\
{																						\
	template<::std::size_t BitSize>														\
	constexpr void derived_from_##id##_impl(id<BitSize>);								\
	template<class T>																	\
	concept derived_from_##id = requires(T t){ _detail::derived_from_##id##_impl(t); };	\
}																						\
//
#define NGS_OS_X86_REGISTER_TAG(id)											\
template<class T>															\
concept id##_register_tag = register_tag<T> && _detail::derived_from_##id<T>\
//
#define NGS_OS_X86_REGISTER(id)														\
NGS_OS_X86_REGISTER_DERIVED_FROM(id);												\
NGS_OS_X86_REGISTER_TAG(id);														\
template<class T>																	\
concept id##_register = register_<T> && id##_register_tag<register_category_t<T>>	\
//

NGS_OS_X86_REGISTER_DERIVED_FROM(basic_register);

template<class T>
concept register_tag = _detail::derived_from_basic_register<T>;

template<class T>
concept register_ = register_tag<register_category_t<T>> /*&& (bits::algorithm::bit_of<bits::bitsets::underlying_type_t<T>>() >= NGS_LIB_MODULE_NAME::register_bit_v<register_category_t<T>>())*/;

NGS_LIB_MODULE_END