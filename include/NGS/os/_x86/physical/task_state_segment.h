#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct alignas(bits::algorithm::bit_to_byte_ceil(32)) task_state_segment_32
{
	::std::uint16_t previous_task_link;
	::std::uint16_t : 16; //padding

	::std::uint32_t esp0;
	::std::uint16_t ss0;
	::std::uint16_t : 16; //padding

	::std::uint32_t esp1;
	::std::uint16_t ss1;
	::std::uint16_t : 16; //padding

	::std::uint32_t esp2;
	::std::uint16_t ss2;
	::std::uint16_t : 16; //padding

	registers::control3 control3;
	registers::instruction_pointer_register instruction_pointer;
	registers::flags_register flags;
	registers::accumulator_register accumulator;
	registers::count_register count;
	registers::data_register data;
	registers::base_register base;
	registers::stack_pointer_register stack_pointer;
	registers::base_pointer_register base_pointer;
	registers::source_index_register source_index;
	registers::destination_index_register destination_index;

	registers::extra_segment extra_segment;
	::std::uint16_t : 16; //padding
	registers::code_segment code_segment;
	::std::uint16_t : 16; //padding
	registers::stack_segment stack_segment;
	::std::uint16_t : 16; //padding
	registers::data_segment data_segment;
	::std::uint16_t : 16; //padding
	registers::more_extra_segment more_extra_segment;
	::std::uint16_t : 16; //padding
	registers::yet_more_extra_segment yet_more_extra_segment;
	::std::uint16_t : 16; //padding
	registers::local_descriptor_table local_descriptor_table;
	::std::uint16_t : 16; //padding

	::std::uint16_t trap : 1;
	::std::uint16_t : 15; //padding

	::std::uint16_t io_map_base_address;

	::std::uint32_t shadow_stack_pointer;
};

NGS_LIB_MODULE_END