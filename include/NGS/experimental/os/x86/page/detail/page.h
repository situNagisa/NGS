#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t Size>
struct basic_page : ::std::array<::std::byte, Size>
{
	NGS_PP_INJECT_BEGIN(basic_page);
public:
	constexpr static auto page_size = Size;

	template<class T>
	explicit(true) operator ::std::span<T, page_size / sizeof(T)>(this auto&& self)
	{
		return ::std::span<T, page_size / sizeof(T)>(reinterpret_cast<T*>(::std::ranges::data(self)), page_size / sizeof(T));
	}

	template<class T>
	explicit(true) operator ::std::span<T>(this auto&& self)
	{
		return ::std::span<T>(reinterpret_cast<T*>(::std::ranges::data(self)), page_size / sizeof(T));
	}
};

template<enums::page_size Size>
using page = basic_page<enums::factor(Size)>;

using page_4_kb = page<enums::page_size::_4kb>;
using page_4_mb = page<enums::page_size::_4mb>;

NGS_LIB_MODULE_END