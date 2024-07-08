#pragma once

#include "./cast.h"
#include "./defined.h"

NGS_LIB_BEGIN

constexpr auto pointer_offset(auto* pointer,::std::ptrdiff_t offset)
{
	using value_type = type_traits::naked_t<::std::remove_pointer_t<decltype(pointer)>>;
	return NGS_LIB_NAME::pointer_cast<value_type>(NGS_LIB_NAME::pointer_cast<::std::uint8_t>(pointer) + offset);
}

NGS_LIB_END