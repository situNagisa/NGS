#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T, class Buffer>
concept contexable = requires(T t, Buffer buffer) { create_context(NGS_PP_PERFECT_FORWARD(t), NGS_PP_PERFECT_FORWARD(buffer)); };

template<class T, class Buffer = ::std::span<::std::byte>>
	requires contexable<T, Buffer>
using parser_context_t = decltype(create_context(::std::declval<T>(), ::std::declval<Buffer>()));

template<class T, class Buffer>
concept parser = contexable<T, Buffer>&& ::std::regular<parser_context_t<T, Buffer>>&& requires(T t, Buffer buffer, parser_context_t<T, Buffer>& context)
{
	{ check(NGS_PP_PERFECT_FORWARD(t), NGS_PP_PERFECT_FORWARD(buffer), context) } -> ::std::convertible_to<bool>;
	{ lose(NGS_PP_PERFECT_FORWARD(t), NGS_PP_PERFECT_FORWARD(buffer), context) } -> ::std::convertible_to<::std::size_t>;
	{ parse(NGS_PP_PERFECT_FORWARD(t), NGS_PP_PERFECT_FORWARD(buffer), context) } -> ::std::convertible_to<::std::size_t>;
};

NGS_LIB_MODULE_END