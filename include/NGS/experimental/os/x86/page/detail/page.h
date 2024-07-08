#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t Size>
struct basic_page final: ::std::ranges::view_interface<basic_page<Size>>
{
	NGS_PP_INJECT(basic_page);
public:
	constexpr static auto page_size() noexcept { return Size; }

	//uninitialized
	::std::array<::std::byte, page_size()> _data;
};

template<enums::page_size Size>
using page = basic_page<enums::factor(Size)>;

using page_4_kb = basic_page<bits::literals::operator ""_kb(4)>;
using page_4_mb = basic_page<bits::literals::operator ""_mb(4)>;

NGS_LIB_MODULE_END

template<::std::size_t Size>
inline constexpr bool ::std::ranges::enable_view<NGS_NS::NGS_LIB_NAME::NGS_LIB_MODULE_NAME::basic_page<Size>> = false;