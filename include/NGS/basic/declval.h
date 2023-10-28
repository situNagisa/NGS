#pragma once

#include "./defined.h"

NGS_BEGIN

#if NGS_COMPILER == NGS_MSVC
#pragma warning(push)
#pragma warning(disable: 6011)
#endif

/**
 * \brief 一般情况下，我们不会使用这个函数，这个函数是用来在编译期获取一个类型的值。
 *
 * \warning 此函数应与`decltype`关键字搭配使用，而不应该调用他，调用会导致未定义行为
 *
 * \return 一个类型的值
*/
template<class _Type, class _Object = std::remove_reference_t<_Type>>
constexpr std::add_rvalue_reference_t<_Object> declval() {
	_Object* ptr = nullptr;
	return std::move(*ptr);
}

#if NGS_COMPILER == NGS_MSVC
#pragma warning(pop)
#endif

NGS_END