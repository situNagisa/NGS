#pragma once

#include "../../register.h"
#include "../../16.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using register_underlying_t = ::std::uint32_t;

template<tags::register_tag Tag>
struct trivial_register
{
	NGS_PP_INJECT_BEGIN(trivial_register);
public:
	using underlying_type = register_underlying_t;
	using register_category_type = Tag;

	constexpr auto value() const noexcept { return _value; }

	underlying_type _value;
};

template<cpt::derived_from_specialization<bit16::trivial_register> Register, tags::register_tag Tag = tags::register_category_t<Register>>
struct extend_trivial_register : Register
{
	NGS_PP_INJECT_EXPLICIT(extend_trivial_register,Register);
public:
	using underlying_type = register_underlying_t;
	using register_category_type = Tag;

	constexpr explicit(false) extend_trivial_register(underlying_type value = {}) noexcept
		: base_type{ static_cast<typename base_type::underlying_type>(value) }
		, _extend{ static_cast<typename base_type::underlying_type>(bits::algorithm::extract(value, bits::algorithm::bit_of<typename base_type::underlying_type>(), bits::algorithm::bit_of<typename base_type::underlying_type>())) }
	{}

	constexpr auto value_16() const noexcept { return base_type::value(); }

	constexpr auto value() const noexcept { return bits::algorithm::fill(base_type::value(), _extend); }

	typename base_type::underlying_type _extend;
};

NGS_LIB_MODULE_END