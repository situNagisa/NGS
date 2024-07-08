#pragma once

#include "../../16.h"
#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


template<tags::register_tag Tag>
struct segment_register
{
	NGS_PP_INJECT_BEGIN(segment_register);
public:
	using underlying_type = ::std::uint16_t;
	using register_category_type = Tag;

	underlying_type requested_privilege : 2;
	underlying_type table_indicator : 1;
	underlying_type index : 13;

	constexpr segment_register() noexcept = default;
	constexpr segment_register(enums::privilege requested_privilege, enums::table_indicator indicator, underlying_type index) noexcept
		: requested_privilege(static_cast<underlying_type>(requested_privilege))
		, table_indicator(static_cast<underlying_type>(indicator))
		, index(index)
	{}
};

//cs
struct code_segment_register : segment_register<tags::cs> {};
//ds
struct data_segment_register : segment_register<tags::cs> {};
//es
struct extra_segment_register : bit16::extra_segment_register {};
//fs
struct more_extra_segment_register : bit16::more_extra_segment_register {};
//gs
struct yet_more_extra_segment_register : bit16::yet_more_extra_segment_register {};
//ss
struct stack_segment_register : bit16::stack_segment_register {};

NGS_LIB_MODULE_END