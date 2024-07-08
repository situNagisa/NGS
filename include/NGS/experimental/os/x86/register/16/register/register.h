#pragma once

#include "../../register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using register_underlying_t = ::std::uint16_t;

template<tags::register_tag Tag>
struct trivial_register
{
	NGS_PP_INJECT_BEGIN(trivial_register);
public:
	using underlying_type = register_underlying_t;
	using register_category_type = Tag;

	constexpr auto low() const noexcept { return static_cast<::std::byte>(_value); }
	constexpr auto high() const noexcept { return static_cast<::std::byte>(bits::algorithm::extract(_value, bits::algorithm::bit_of<::std::byte>(), bits::algorithm::bit_of<::std::byte>())); }

	constexpr auto value() const noexcept { return _value; }

	underlying_type _value;
};

NGS_LIB_MODULE_END