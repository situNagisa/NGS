#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct blend_state
{
private:
	struct attachment
	{
	private:
		enum class factor_type
		{
			zero,
			one,
			source_color,
			inverse_source_color,
			source_alpha,
			inverse_source_alpha,
			destination_alpha,
			inverse_destination_alpha,
			destination_color,
			inverse_destination_color,
			source_alpha_saturate,
			blend_factor,
			inverse_blend_factor,
			source1_color,
			inverse_source1_color,
			source1_alpha,
			inverse_source1_alpha
		};
		enum class operate_type
		{
			add,
			subtract,
			reverse_subtract,
			min,
			max
		};
		enum class write_type
		{
			red = 1,
			green = 2,
			blue = 4,
			alpha = 8,
			all = red | green | blue | alpha
		};
	public:
		bool enable = false;
		struct
		{
			factor_type source = factor_type::zero;
			factor_type destination = factor_type::zero;
			operate_type operate = operate_type::add;
		}color{};
		struct
		{
			factor_type source = factor_type::zero;
			factor_type destination = factor_type::zero;
			operate_type operate = operate_type::add;
		}alpha{};
		flags::enum_flag<write_type> write_mask = write_type::all;
	};
	enum class logic_operate_type
	{
		clear,
		and_,
		and_reverse,
		copy,
		and_inverted,
		no_op,
		xor_,
		or_,
		nor,
		equivalent,
		invert,
		or_reverse,
		copy_inverted,
		or_inverted,
		nand,
		set
	};
public:
	struct
	{
		bool enable = false;
		logic_operate_type operate = logic_operate_type::clear;
	}logic{};
	::std::span<attachment> attachments{};

	union
	{
		struct
		{
			float red = 0.0f;
			float green = 0.0f;
			float blue = 0.0f;
			float alpha = 0.0f;
		};
		float constants[4];
	};
};

NGS_LIB_MODULE_END