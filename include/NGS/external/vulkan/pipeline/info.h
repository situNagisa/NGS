#pragma once

#include "./module.h"
#include "./defined.h"

NGS_LIB_BEGIN

namespace enums
{
	using shader_stage_bit = ::vk::ShaderStageFlagBits;
	using shader_stage_flag = ::vk::ShaderStageFlags;

	using vertex_input_rate_type = ::vk::VertexInputRate;
	using primitive_topology_type = ::vk::PrimitiveTopology;

	using polygon_mode_type = ::vk::PolygonMode;
	using cull_mode_type = ::vk::CullModeFlagBits;
	using front_face_type = ::vk::FrontFace;

	using sample_count_flag = ::vk::SampleCountFlagBits;

	using compare_operate_type = ::vk::CompareOp;
	using stencil_operate_type = ::vk::StencilOp;

	using blend_factor = ::vk::BlendFactor;
	using blend_operate_type = ::vk::BlendOp;
	using color_component_bit = ::vk::ColorComponentFlagBits;
	using color_component_flag = ::vk::ColorComponentFlags;
	using logic_operate_type = ::vk::LogicOp;

	using dynamic_state_type = ::vk::DynamicState;
}

NGS_LIB_END
NGS_LIB_MODULE_BEGIN

struct info
{
	NGS_MPL_ENVIRON_BEGIN(info);
public:
	using vulkan_type = VkGraphicsPipelineCreateInfo;

	struct shader_type
	{
		using vulkan_type = VkPipelineShaderStageCreateInfo;

		vulkan_struct structure{ ::vk::PipelineShaderStageCreateInfo::structureType };
		enums::shader_stage_flag stage{};
		VkShaderModule shader_module{};
		const char* entry_point{};
		void_ptr_cst specialization_info = nullptr;

		vulkan_type to_vulkan()const
		{
			return
			{
				.sType = static_cast<VkStructureType>(structure.type),
				.pNext = structure.next,
				.flags = structure.flags,
				.stage = static_cast<VkShaderStageFlagBits>(static_cast<enums::shader_stage_flag::MaskType>(stage)),
				.module = shader_module,
				.pName = entry_point,
				.pSpecializationInfo = static_cast<const VkSpecializationInfo*>(specialization_info),
			};
		}
	};
	static_assert(vulkan_info<shader_type>);

	struct vertex_input_type
	{
		using vulkan_type = VkPipelineVertexInputStateCreateInfo;

		struct binding_type
		{
			using vulkan_type = VkVertexInputBindingDescription;

			uint32_t binding{};
			uint32_t stride{};
			enums::vertex_input_rate_type input_rate{};
		};
		static_assert(vulkan_info<binding_type>);

		struct attribute_type
		{
			using vulkan_type = VkVertexInputAttributeDescription;

			uint32_t location{};
			uint32_t binding{};
			format_t format{};
			uint32_t offset{};
		};
		static_assert(vulkan_info<attribute_type>);

		vulkan_struct structure{ ::vk::PipelineVertexInputStateCreateInfo::structureType };
		vulkan_range<binding_type> bindings{};
		vulkan_range<attribute_type> attributes{};

		vulkan_type to_vulkan()const
		{
			return {
				.sType = static_cast<VkStructureType>(structure.type),
				.pNext = structure.next,
				.flags = structure.flags,
				.vertexBindingDescriptionCount = bindings.size(),
				.pVertexBindingDescriptions = reinterpret_cast<const VkVertexInputBindingDescription*>(bindings.data()),
				.vertexAttributeDescriptionCount = attributes.size(),
				.pVertexAttributeDescriptions = reinterpret_cast<const VkVertexInputAttributeDescription*>(attributes.data()),
			};
		}
	};
	static_assert(vulkan_info<vertex_input_type>);

	struct input_assembly_type
	{
		using vulkan_type = VkPipelineInputAssemblyStateCreateInfo;

		vulkan_struct structure{ ::vk::PipelineInputAssemblyStateCreateInfo::structureType };
		enums::primitive_topology_type topology{};
		bool primitive_restart_enable = false;

		vulkan_type to_vulkan()const
		{
			return {
				.sType = static_cast<VkStructureType>(structure.type),
				.pNext = structure.next,
				.flags = structure.flags,
				.topology = static_cast<VkPrimitiveTopology>(topology),
				.primitiveRestartEnable = primitive_restart_enable,
			};
		}
	};
	static_assert(vulkan_info<input_assembly_type>);

	struct tessellation_type
	{
		using vulkan_type = VkPipelineTessellationStateCreateInfo;

		vulkan_struct structure{ ::vk::PipelineTessellationStateCreateInfo::structureType };
		uint32_t patch_control_points{};

		vulkan_type to_vulkan()const
		{
			return {
				.sType = static_cast<VkStructureType>(structure.type),
				.pNext = structure.next,
				.flags = structure.flags,
				.patchControlPoints = patch_control_points,
			};
		}
	};
	static_assert(vulkan_info<tessellation_type>);

	struct viewport_state_type
	{
		using vulkan_type = VkPipelineViewportStateCreateInfo;

		struct viewport_type : math::boxes::containers::hypercube<3, float>
		{
			NGS_MPL_ENVIRON(viewport_type);
		public:
			using vulkan_type = VkViewport;

			using base_type::base_type;
			using base_type::operator=;

			vulkan_type to_vulkan()const
			{
				return {
					.x = base_type::position()[0],
					.y = base_type::position()[1],
					.width = base_type::size()[0],
					.height = base_type::size()[1],
					.minDepth = base_type::position()[2],
					.maxDepth = base_type::position()[2] + base_type::size()[2],
				};
			}
		};
		static_assert(vulkan_info<viewport_type>);

		struct scissor_type : math::boxes::containers::hypercube<2, int32_t, uint32_t>
		{
			NGS_MPL_ENVIRON(scissor_type);
		public:
			using vulkan_type = VkRect2D;

			using base_type::base_type;
			using base_type::operator=;

			vulkan_type to_vulkan()const
			{
				return {
					.offset = { base_type::position()[0],base_type::position()[1] },
					.extent = { base_type::size()[0],base_type::size()[1] },
				};
			}
		};
		static_assert(vulkan_info<scissor_type>);

		vulkan_struct structure{ ::vk::PipelineViewportStateCreateInfo::structureType };
		vulkan_range<viewport_type> viewports{};
		vulkan_range<scissor_type> scissors{};

		vulkan_type to_vulkan()const
		{
			return
			{
				.sType = static_cast<VkStructureType>(structure.type),
				.pNext = structure.next,
				.flags = structure.flags,
				.viewportCount = viewports.size(),
				.pViewports = reinterpret_cast<const VkViewport*>(viewports.data()),
				.scissorCount = scissors.size(),
				.pScissors = reinterpret_cast<const VkRect2D*>(scissors.data()),
			};
		}
	};
	static_assert(vulkan_info<viewport_state_type>);

	struct rasterization_type
	{
		using vulkan_type = VkPipelineRasterizationStateCreateInfo;

		vulkan_struct structure{ ::vk::PipelineRasterizationStateCreateInfo::structureType };
		bool depth_clamp_enable = false;
		bool rasterizer_discard_enable = false;
		enums::polygon_mode_type polygon_mode{};
		enums::cull_mode_type cull_mode{};
		enums::front_face_type front_face{};
		bool depth_bias_enable = false;
		float depth_bias_constant_factor{};
		float depth_bias_clamp{};
		float depth_bias_slope_factor{};
		float line_width{};

		vulkan_type to_vulkan()const
		{
			return
			{
				.sType = static_cast<VkStructureType>(structure.type),
				.pNext = structure.next,
				.flags = structure.flags,
				.depthClampEnable = depth_clamp_enable,
				.rasterizerDiscardEnable = rasterizer_discard_enable,
				.polygonMode = static_cast<VkPolygonMode>(polygon_mode),
				.cullMode = static_cast<VkCullModeFlags>(cull_mode),
				.frontFace = static_cast<VkFrontFace>(front_face),
				.depthBiasEnable = depth_bias_enable,
				.depthBiasConstantFactor = depth_bias_constant_factor,
				.depthBiasClamp = depth_bias_clamp,
				.depthBiasSlopeFactor = depth_bias_slope_factor,
				.lineWidth = line_width,
			};
		}
	};
	static_assert(vulkan_info<rasterization_type>);

	struct multi_sample_type
	{
		using vulkan_type = VkPipelineMultisampleStateCreateInfo;

		vulkan_struct structure{ ::vk::PipelineMultisampleStateCreateInfo::structureType };
		enums::sample_count_flag rasterization_samples{};
		bool sample_shading_enable = false;
		float min_sample_shading{};
		const uint32_t* sample_mask = nullptr;
		bool alpha_to_coverage_enable = false;
		bool alpha_to_one_enable = false;

		vulkan_type to_vulkan()const
		{
			return
			{
				.sType = static_cast<VkStructureType>(structure.type),
				.pNext = structure.next,
				.flags = structure.flags,
				.rasterizationSamples = static_cast<VkSampleCountFlagBits>(rasterization_samples),
				.sampleShadingEnable = sample_shading_enable,
				.minSampleShading = min_sample_shading,
				.pSampleMask = sample_mask,
				.alphaToCoverageEnable = alpha_to_coverage_enable,
				.alphaToOneEnable = alpha_to_one_enable,
			};
		}
	};
	static_assert(vulkan_info<multi_sample_type>);

	struct depth_stencil_type
	{
		using vulkan_type = VkPipelineDepthStencilStateCreateInfo;

		vulkan_struct structure{ ::vk::PipelineDepthStencilStateCreateInfo::structureType };
		bool depth_test_enable = false;
		bool depth_write_enable = false;
		enums::compare_operate_type depth_compare_op{};
		bool depth_bounds_test_enable = false;
		bool stencil_test_enable = false;
		struct
		{
			enums::compare_operate_type compare_op{};
			uint32_t reference{};
			uint32_t compare_mask{};
			uint32_t write_mask{};
			uint32_t fail_op{};
			uint32_t pass_op{};
			uint32_t depth_fail_op{};
		}front{}, back{};
		math::boxes::containers::minmax<float, 1> depth_bounds{};

		vulkan_type to_vulkan()const
		{
			return
			{
				.sType = static_cast<VkStructureType>(structure.type),
				.pNext = structure.next,
				.flags = structure.flags,
				.depthTestEnable = depth_test_enable,
				.depthWriteEnable = depth_write_enable,
				.depthCompareOp = static_cast<VkCompareOp>(depth_compare_op),
				.depthBoundsTestEnable = depth_bounds_test_enable,
				.stencilTestEnable = stencil_test_enable,
				.front = VkStencilOpState
				{
					.failOp = static_cast<VkStencilOp>(front.fail_op),
					.passOp = static_cast<VkStencilOp>(front.pass_op),
					.depthFailOp = static_cast<VkStencilOp>(front.depth_fail_op),
					.compareOp = static_cast<VkCompareOp>(front.compare_op),
					.compareMask = front.compare_mask,
					.writeMask = front.write_mask,
					.reference = front.reference,
				},
				.back = VkStencilOpState
				{
					.failOp = static_cast<VkStencilOp>(back.fail_op),
					.passOp = static_cast<VkStencilOp>(back.pass_op),
					.depthFailOp = static_cast<VkStencilOp>(back.depth_fail_op),
					.compareOp = static_cast<VkCompareOp>(back.compare_op),
					.compareMask = back.compare_mask,
					.writeMask = back.write_mask,
					.reference = back.reference,
				},
				.minDepthBounds = depth_bounds.min()[0],
				.maxDepthBounds = depth_bounds.max()[0],
			};
		}
	};
	static_assert(vulkan_info<depth_stencil_type>);

	struct color_blend_type
	{
		using vulkan_type = VkPipelineColorBlendStateCreateInfo;

		struct attachment_type
		{
			using vulkan_type = VkPipelineColorBlendAttachmentState;

			bool blend_enable = false;
			struct
			{
				enums::blend_factor source{};
				enums::blend_factor destination{};
				enums::blend_operate_type operate{};
			}color{}, alpha{};
			enums::color_component_flag color_write_mask{};

			auto to_vulkan()const
			{
				return vulkan_type
				{
					.blendEnable = blend_enable,
					.srcColorBlendFactor = static_cast<VkBlendFactor>(color.source),
					.dstColorBlendFactor = static_cast<VkBlendFactor>(color.destination),
					.colorBlendOp = static_cast<VkBlendOp>(color.operate),
					.srcAlphaBlendFactor = static_cast<VkBlendFactor>(alpha.source),
					.dstAlphaBlendFactor = static_cast<VkBlendFactor>(alpha.destination),
					.alphaBlendOp = static_cast<VkBlendOp>(alpha.operate),
					.colorWriteMask = static_cast<VkColorComponentFlags>(color_write_mask),
				};
			}
		};
		static_assert(vulkan_info<attachment_type>);

		vulkan_struct structure{ ::vk::PipelineColorBlendStateCreateInfo::structureType };
		bool logic_op_enable = false;
		enums::logic_operate_type logic_op{};
		vulkan_range<attachment_type> attachments{};
	private:
		struct _constant
		{
			float red{};
			float green{};
			float blue{};
			float alpha{};
		};
	public:
		union {
			_constant constant;
			float constants[4]{};
		};

		vulkan_type to_vulkan()const
		{
			return
			{
				.sType = static_cast<VkStructureType>(structure.type),
				.pNext = structure.next,
				.flags = structure.flags,
				.logicOpEnable = logic_op_enable,
				.logicOp = static_cast<VkLogicOp>(logic_op),
				.attachmentCount = attachments.size(),
				.pAttachments = reinterpret_cast<const VkPipelineColorBlendAttachmentState*>(attachments.data()),
				.blendConstants = { constants[0],constants[1],constants[2],constants[3] },
			};
		}
	};
	static_assert(vulkan_info<color_blend_type>);

	struct dynamic_state_type
	{
		using vulkan_type = VkPipelineDynamicStateCreateInfo;

		vulkan_struct structure{ ::vk::PipelineDynamicStateCreateInfo::structureType };
		vulkan_range<enums::dynamic_state_type> states{};

		vulkan_type to_vulkan()const
		{
			return
			{
				.sType = static_cast<VkStructureType>(structure.type),
				.pNext = structure.next,
				.flags = structure.flags,
				.dynamicStateCount = states.size(),
				.pDynamicStates = reinterpret_cast<const VkDynamicState*>(states.data()),
			};
		}
	};
	static_assert(vulkan_info<dynamic_state_type>);

	vulkan_struct structure{ trait::structure_type };
	vulkan_range<shader_type> stages{};
	vertex_input_type vertex_input{};
	input_assembly_type input_assembly{};
	tessellation_type tessellation{};
	viewport_state_type viewport_state{};
	rasterization_type rasterization{};
	multi_sample_type multi_sample{};
	depth_stencil_type depth_stencil{};
	color_blend_type color_blend{};
	dynamic_state_type dynamic_state{};
	uint32_t subpass{};
	int32_t base_pipeline_index{};

	static auto create(const self_type& self, const VkDevice& device, const VkPipelineLayout& layout, const VkRenderPass& render_pass, const VkPipeline& pipeline)
	{
		auto vertex_input = NGS_LIB_NAME::to_vulkan(self.vertex_input);
		auto input_assembly = NGS_LIB_NAME::to_vulkan(self.input_assembly);
		auto tessellation = NGS_LIB_NAME::to_vulkan(self.tessellation);

		auto viewports = NGS_LIB_NAME::to_vulkan_vector(self.viewport_state.viewports);
		auto scissors = NGS_LIB_NAME::to_vulkan_vector(self.viewport_state.scissors);
		auto viewport = NGS_LIB_NAME::to_vulkan(self.viewport_state);
		viewport.viewportCount = static_cast<uint32_t>(viewports.size());
		viewport.pViewports = viewports.data();
		viewport.scissorCount = static_cast<uint32_t>(scissors.size());
		viewport.pScissors = scissors.data();

		auto rasterization = NGS_LIB_NAME::to_vulkan(self.rasterization);
		auto multi_sample = NGS_LIB_NAME::to_vulkan(self.multi_sample);
		auto depth_stencil = NGS_LIB_NAME::to_vulkan(self.depth_stencil);

		auto attachments = NGS_LIB_NAME::to_vulkan_vector(self.color_blend.attachments);
		auto color_blend = NGS_LIB_NAME::to_vulkan(self.color_blend);
		color_blend.attachmentCount = static_cast<uint32_t>(attachments.size());
		color_blend.pAttachments = attachments.data();

		auto dynamic = NGS_LIB_NAME::to_vulkan(self.dynamic_state);

		auto stages = NGS_LIB_NAME::to_vulkan_vector(self.stages);

		VkGraphicsPipelineCreateInfo create_info = {};
		create_info.sType = static_cast<VkStructureType>(self.structure.type);
		create_info.pNext = self.structure.next;
		create_info.flags = self.structure.flags;
		create_info.stageCount = static_cast<uint32_t>(stages.size());
		create_info.pStages = stages.data();
		create_info.pVertexInputState = &vertex_input;
		create_info.pInputAssemblyState = &input_assembly;
		create_info.pTessellationState = &tessellation;
		create_info.pViewportState = &viewport;
		create_info.pRasterizationState = &rasterization;
		create_info.pMultisampleState = &multi_sample;
		create_info.pDepthStencilState = &depth_stencil;
		create_info.pColorBlendState = &color_blend;
		create_info.pDynamicState = &dynamic;
		create_info.layout = layout;
		create_info.renderPass = render_pass;
		create_info.subpass = self.subpass;
		create_info.basePipelineHandle = pipeline;
		create_info.basePipelineIndex = self.base_pipeline_index;

		trait::entity_type result{};
		auto success = trait::create_functor(device, VK_NULL_HANDLE, 1, &create_info, nullptr, &result);
		NGS_ASSERT(success == VK_SUCCESS, "failed to create graphics pipeline");
		return result;
	}
	static void destroy(const VkDevice& device, const trait::entity_type& entity)
	{
		trait::destroy_functor(device, entity, nullptr);
	}
};

NGS_LIB_MODULE_END