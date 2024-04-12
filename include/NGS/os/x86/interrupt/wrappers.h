#pragma once

#include "../fieldset.h"
#include "./descriptor.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct task_gate : fieldsets::wrapper<gate_descriptor>
{
	NGS_MPL_ENVIRON(task_gate);
public:
	using base_type::underlying_type;

	using base_type::base_type;
	using base_type::operator=;

	constexpr task_gate(
		::std::uint16_t selector,
		underlying_type privilege_level,
		bool present
	)
		: base_type({
			.offset_low = static_cast<underlying_type>(0),
			.cs = selector,
			.param = 0,
			.zero = 0,
			.type = base_type::filed_set_type::gate_type::task,
			.s = 0,
			.dpl = privilege_level,
			.p = present,
			.offset_high = static_cast<underlying_type>(0),
		})
	{}
};

struct call_gate : fieldsets::wrapper<gate_descriptor>
{
	NGS_MPL_ENVIRON(call_gate);
public:
	using base_type::underlying_type;

	using base_type::base_type;
	using base_type::operator=;

	constexpr call_gate(
		::std::uint16_t selector,
		underlying_type offset,
		underlying_type privilege_level,
		bool present
	)
		: base_type({
			.offset_low = static_cast<underlying_type>((offset >> 0) & 0xFFFF),
			.cs = selector,
			.param = 0,
			.zero = 0,
			.type = base_type::filed_set_type::gate_type::call,
			.s = 0,
			.dpl = privilege_level,
			.p = present,
			.offset_high = static_cast<underlying_type>((offset >> 16) & 0xFFFF),
		})
	{}
};

namespace _detail
{
	template<enum gate_descriptor::gate_type Type>
	struct basic_gate : fieldsets::wrapper<gate_descriptor>
	{
		NGS_MPL_ENVIRON(basic_gate);
	public:
		using base_type::underlying_type;

		using base_type::base_type;
		using base_type::operator=;

		constexpr basic_gate(
			::std::uint16_t selector,
			::std::uint32_t offset,
			underlying_type privilege_level,
			bool present
		)
			: base_type({
				.offset_low = static_cast<underlying_type>((offset >> 0) & 0xFFFF),
				.cs = selector,
				.param = 0,
				.zero = 0,
				.type = Type,
				.s = 0,
				.dpl = privilege_level,
				.p = present,
				.offset_high = static_cast<underlying_type>((offset >> 16) & 0xFFFF),
			})
		{}
	};
}

using trap_16_gate = _detail::basic_gate<gate_descriptor::gate_type::trap_16>;
using trap_32_gate = _detail::basic_gate<gate_descriptor::gate_type::trap_32>;
using interrupt_16_gate = _detail::basic_gate<gate_descriptor::gate_type::interrupt_16>;
using interrupt_32_gate = _detail::basic_gate<gate_descriptor::gate_type::interrupt_32>;

NGS_LIB_MODULE_END