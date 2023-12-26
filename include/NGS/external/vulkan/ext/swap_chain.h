#pragma once

#include "../info.h"
#include "./defined.h"

NGS_EXTERNAL_VULKAN_INFO_ENVIRONMENT(SwapchainCreateInfoKHR);
NGS_LIB_MODULE_BEGIN

namespace swap_chains
{
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(image_count, VkSwapchainCreateInfoKHR, size_t, minImageCount);
	constexpr auto format(const VkSurfaceFormatKHR& format)
	{
		return [=](VkSwapchainCreateInfoKHR& info) -> VkSwapchainCreateInfoKHR&
			{
				info.imageFormat = format.format;
				info.imageColorSpace = format.colorSpace;
				return info;
			};
	};
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(format, VkSwapchainCreateInfoKHR, VkFormat, imageFormat);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(format, VkSwapchainCreateInfoKHR, ::vk::Format, imageFormat);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(color_space, VkSwapchainCreateInfoKHR, VkColorSpaceKHR, imageColorSpace);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(color_space, VkSwapchainCreateInfoKHR, ::vk::ColorSpaceKHR, imageColorSpace);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(extent, VkSwapchainCreateInfoKHR, VkExtent2D, imageExtent);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(array_layers, VkSwapchainCreateInfoKHR, size_t, imageArrayLayers);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(usage, VkSwapchainCreateInfoKHR, VkImageUsageFlags, imageUsage);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(sharing_mode, VkSwapchainCreateInfoKHR, VkSharingMode, imageSharingMode);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(sharing_mode, VkSwapchainCreateInfoKHR, ::vk::SharingMode, imageSharingMode);
	constexpr auto image(size_t count, const VkSurfaceFormatKHR& f, const VkExtent2D& e, size_t layer_count, const VkImageUsageFlags& u, const VkSharingMode& s)
	{
		return [=](VkSwapchainCreateInfoKHR& info) -> VkSwapchainCreateInfoKHR&
			{
				image_count(count)(info);
				format(f)(info);
				extent(e)(info);
				array_layers(layer_count)(info);
				usage(u)(info);
				sharing_mode(s)(info);
				return info;
			};
	};
	constexpr auto image(size_t count, const ::vk::SurfaceFormatKHR& f, const ::vk::Extent2D& extent, size_t layer_count, const ::vk::ImageUsageFlags& usage, const ::vk::SharingMode& sharing_mode)
	{
		return image(count, static_cast<VkSurfaceFormatKHR>(f), extent, layer_count, static_cast<VkImageUsageFlags>(usage), static_cast<VkSharingMode>(sharing_mode));
	};
	constexpr auto family(::std::span<const uint32_t> indices)
	{
		return [=](VkSwapchainCreateInfoKHR& info) -> VkSwapchainCreateInfoKHR&
			{
				info.queueFamilyIndexCount = static_cast<uint32_t>(indices.size());
				info.pQueueFamilyIndices = indices.data();
				return info;
			};
	};
	constexpr auto family(::std::initializer_list<uint32_t> indices) { return family(::std::span(indices)); };

	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(pre_transform, VkSwapchainCreateInfoKHR, VkSurfaceTransformFlagBitsKHR, preTransform);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(pre_transform, VkSwapchainCreateInfoKHR, ::vk::SurfaceTransformFlagBitsKHR, preTransform);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(composite_alpha, VkSwapchainCreateInfoKHR, VkCompositeAlphaFlagBitsKHR, compositeAlpha);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(composite_alpha, VkSwapchainCreateInfoKHR, ::vk::CompositeAlphaFlagBitsKHR, compositeAlpha);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(present_mode, VkSwapchainCreateInfoKHR, VkPresentModeKHR, presentMode);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(present_mode, VkSwapchainCreateInfoKHR, ::vk::PresentModeKHR, presentMode);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(clipped, VkSwapchainCreateInfoKHR, bool, clipped);
	NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(old_swap_chain, VkSwapchainCreateInfoKHR, VkSwapchainKHR, oldSwapchain);
}

NGS_LIB_MODULE_END
