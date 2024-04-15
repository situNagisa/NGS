#pragma once

#include "./trait.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<fieldset FieldSet>
struct wrapper
{
	NGS_MPL_ENVIRON_BEGIN(wrapper);
public:
	using filed_set_type = FieldSet;
	using underlying_type = underlying_type_t<filed_set_type>;

	constexpr wrapper() = default;
	constexpr explicit(false) wrapper(const filed_set_type& other) : _value(other) {}
	constexpr explicit(false) wrapper(filed_set_type&& other) : _value(::std::move(other)) {}
	constexpr explicit(false) wrapper(const underlying_type& value) : _value(creator_v<register_type>(value)) {}

	constexpr auto&& register_() { return _value; }
	constexpr auto&& register_()const { return _value; }

	constexpr auto value()const { static_cast<underlying_type>(_value); }

	filed_set_type _value{};
};

NGS_LIB_MODULE_END