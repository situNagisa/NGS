#pragma once

#include "./pipeline.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct descriptor_set_type
{
	enum class bits
	{
		update_after_bind_pool,
	};
	struct binding_layout_type
	{
		enum class descriptor_type
		{
			sampler,
			combined_image_sampler,
			sampled_image,
			uniform_texture_buffer,
			storage_texture_buffer,
			uniform_buffer,
			storage_buffer,
			uniform_buffer_dynamic,
			storage_buffer_dynamic,
			input_attachment,
			inline_uniform_block,
		};

		binding_type binding = 0;
		descriptor_type descriptor = descriptor_type::sampler;
		shader_stage_flag stage{};
		size_type count = 0;
	};

	flags::enum_flag<bits> flags{};
	::std::span<binding_layout_type> bindings{};
};

NGS_LIB_MODULE_END