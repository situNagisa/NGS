#pragma once

#include "./basic.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<class BitType> requires ::std::is_enum_v<BitType>
struct enum_flag : basic_flag<enum_flag<BitType>, ::std::underlying_type_t<BitType>>
{
	NGS_PP_INJECT_EXPLICIT(enum_flag, basic_flag<enum_flag<BitType>, ::std::underlying_type_t<BitType>>);
public:
	NGS_PP_INHERIT_TYPE_EXPLICIT(value_type, base_type);
	using bit_type = BitType;

	using base_type::base_type;
	constexpr enum_flag(bit_type bit) : base_type(static_cast<value_type>(bit)) {}

	constexpr self_type& operator=(const self_type&) = default;
	constexpr bool operator==(const self_type&)const = default;
};


NGS_LIB_END