#pragma once

#include "../register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct alignas(bits::algorithm::bit_to_byte_ceil(32)) task_state_segment_32
{
	::std::uint16_t previous_task_link;
	::std::uint16_t : 16; //padding

	stack_pointer_register esp0;
	stack_segment_register ss0;
	::std::uint16_t : 16; //padding

	stack_pointer_register esp1;
	stack_segment_register ss1;
	::std::uint16_t : 16; //padding

	stack_pointer_register esp2;
	stack_segment_register ss2;
	::std::uint16_t : 16; //padding

	control3_register control3;
	instruction_pointer_register instruction_pointer;
	flags_register flags;
	accumulator_register accumulator;
	counter_register count;
	data_register data;
	base_register base;
	stack_pointer_register stack_pointer;
	base_pointer_register base_pointer;
	source_index_register source_index;
	destination_index_register destination_index;

	extra_segment_register extra_segment;
	::std::uint16_t : 16; //padding
	code_segment_register code_segment;
	::std::uint16_t : 16; //padding
	stack_segment_register stack_segment;
	::std::uint16_t : 16; //padding
	data_segment_register data_segment;
	::std::uint16_t : 16; //padding
	more_extra_segment_register more_extra_segment;
	::std::uint16_t : 16; //padding
	yet_more_extra_segment_register yet_more_extra_segment;
	::std::uint16_t : 16; //padding
	local_descriptor_table_register local_descriptor_table;
	::std::uint16_t : 16; //padding

	::std::uint16_t trap : 1;
	::std::uint16_t : 15; //padding

	::std::uint16_t io_map_base_address;

	::std::uintptr_t shadow_stack_pointer;
};

NGS_LIB_MODULE_END