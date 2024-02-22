#pragma once

#include "./basic.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<class _BitType> requires ::std::is_enum_v<_BitType>
struct enum_flag : basic_flag<enum_flag<_BitType>, ::std::underlying_type_t<_BitType>>
{
	NGS_MPL_ENVIRON2(enum_flag, basic_flag<enum_flag<_BitType>, ::std::underlying_type_t<_BitType>>);
public:
	NGS_MPL_INHERIT_TYPE(value_type, base_type);
	using bit_type = _BitType;

	using base_type::base_type;
	constexpr enum_flag(bit_type bit) : base_type(static_cast<value_type>(bit)) {}

	constexpr self_type& operator=(const self_type&) = default;
	constexpr bool operator==(const self_type&)const = default;
};


NGS_LIB_END