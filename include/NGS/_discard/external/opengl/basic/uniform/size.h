#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class T>
	struct size : ccpt::auto_constant<0> {};

	template<class T, ::std::size_t Size>
	struct size<T[Size]> : ccpt::auto_constant<Size> {};

	template<class T, ::std::size_t Size>
	struct size<::std::array<T, Size>> : ccpt::auto_constant<Size> {};

	template<class T, ::std::size_t Size> requires (Size != ::std::dynamic_extent)
	struct size<::std::span<T,Size>> : ccpt::auto_constant<Size> {};
}

NGS_LIB_MODULE_END