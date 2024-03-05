#pragma once

#include "../variable.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

/// @brief 包装类型为`元变量`
/// @note
///		`meta_variable`无法嵌套！
///		换言之: 若`T`为`meta_variable`的特化，则`meta_variable<meta_variable<T>>`等价于`meta_variable<T>`
template<class T>
struct meta_variable {
	using value_type = T;
	static constexpr ::std::size_t size = sizeof(value_type);// layout::size_of<value_type>();
	static constexpr layout::align_t align = layout::align_of<value_type>();
};

template<variables::variable T>
struct meta_variable<T> : T {};

NGS_LIB_MODULE_END
