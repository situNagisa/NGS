#pragma once

#include "../basic.h"
#include "./module.h"
#include "./defined.h"


NGS_LIB_BEGIN
namespace enums
{
	using image_layout_type = ::vk::ImageLayout;

	enum class sampler_count_bit : flag_t
	{
		_1 = 1ul << 0,
		_2 = 1ul << 1,
		_4 = 1ul << 2,
		_8 = 1ul << 3,
		_16 = 1ul << 4,
		_32 = 1ul << 5,
		_64 = 1ul << 6,
	};
	using sampler_count_flag = flags::enum_flag<sampler_count_bit>;

	using load_operate_type = ::vk::AttachmentLoadOp;
	using store_operate_type = ::vk::AttachmentStoreOp;

	using pipeline_bind_point_type = ::vk::PipelineBindPoint;

	using pipeline_stage_bit = ::vk::PipelineStageFlagBits;
	using pipeline_stage_flag = ::vk::PipelineStageFlags;

	using access_bit = ::vk::AccessFlagBits;
	using access_flag = ::vk::AccessFlags;

	using dependency_bit = ::vk::DependencyFlagBits;
	using dependency_flag = ::vk::DependencyFlags;
}
NGS_LIB_END
NGS_LIB_MODULE_BEGIN

struct info
{
	NGS_MPL_ENVIRON_BEGIN(info);
public:
	using vulkan_type = trait::info_type;

	struct attachment_type
	{
		using vulkan_type = VkAttachmentDescription;

		flag_t flags{};
		format_t format{};
		enums::sampler_count_flag samples{};
		struct
		{
			enums::load_operate_type load{};
			enums::store_operate_type store{};
		} normal{}, stencil{};
		struct
		{
			enums::image_layout_type initial{};
			enums::image_layout_type final{};
		}layout{};
	};
	static_assert(vulkan_info<attachment_type>);

	struct attachment_reference_type
	{
		using vulkan_type = VkAttachmentReference;

		uint32_t attachment{};
		enums::image_layout_type layout{};
	};
	static_assert(vulkan_info<attachment_reference_type>);

	struct subpass_type
	{
		using vulkan_type = VkSubpassDescription;

		flag_t flags{};
		enums::pipeline_bind_point_type pipeline_bind_point{};
		struct
		{
			vulkan_range<attachment_reference_type> input{};
			vulkan_range<attachment_reference_type> color{};
			const attachment_reference_type* resolve = nullptr;
			const attachment_reference_type* depth_stencil = nullptr;
			vulkan_range<uint32_t> preserve{};
		}attachment{};
	};
	static_assert(vulkan_info<subpass_type>);
	int a = sizeof(enums::pipeline_bind_point_type);
	struct subpass_dependency_type
	{
		using vulkan_type = VkSubpassDependency;

		struct
		{
			uint32_t source{};
			uint32_t destination{};
		}subpass{};
		struct
		{
			enums::pipeline_stage_flag source{};
			enums::pipeline_stage_flag destination{};
		}stage{};
		struct
		{
			enums::access_flag source{};
			enums::access_flag destination{};
		}access{};
		enums::dependency_flag flags{};
	};
	static_assert(vulkan_info<subpass_dependency_type>);

	vulkan_struct structure{ trait::structure_type };
	vulkan_range<attachment_type> attachments{};
	vulkan_range<subpass_type> subpasses{};
	vulkan_range<subpass_dependency_type> dependencies{};

	auto to_vulkan()const
	{
		return vulkan_type{
			.sType = static_cast<VkStructureType>(structure.type),
			.pNext = structure.next,
			.flags = structure.flags,
			.attachmentCount = attachments.size(),
			.pAttachments = attachments.vulkan_data(),
			.subpassCount = subpasses.size(),
			.pSubpasses = subpasses.vulkan_data(),
			.dependencyCount = dependencies.size(),
			.pDependencies = dependencies.vulkan_data(),
		};
	}

	static auto create(const self_type& self, const VkDevice& device)
	{
		trait::entity_type result{};

		auto&& vulkan_info = NGS_LIB_NAME::to_vulkan(self);

		trait::create_functor(device, &vulkan_info, nullptr, &result);

		return result;
	}

	static void destroy(const VkDevice& device, const trait::entity_type& entity)
	{
		trait::destroy_functor(device, entity, nullptr);
	}
};
static_assert(vulkan_info<info>);

NGS_LIB_MODULE_END