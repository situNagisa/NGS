#pragma once

#include "../info.h"
#include "./defined.h"

NGS_EXTERNAL_VULKAN_INFO_ENVIRONMENT(PipelineShaderStageCreateInfo);
NGS_LIB_BEGIN
struct shader
{
	NGS_MPL_ENVIRON_BEGIN(shader);
public:
	shader(::vk::Device device, ::std::ranges::contiguous_range auto&& code)
		: shader(device, {
			reinterpret_cast<uint32_ptr_cst>(::std::ranges::data(NGS_PP_PERFECT_FORWARD(code))),
				sizeof(::std::ranges::range_value_t<decltype(code)>) * ::std::ranges::size(NGS_PP_PERFECT_FORWARD(code))
			}) {}
	shader(::vk::Device device, ::std::span<const uint32_t> code) : shader(device, ::vk::ShaderModuleCreateInfo({}, code.size(), code.data())) {}
	shader(::vk::Device device, const VkShaderModuleCreateInfo& info);
	~shader();

	void set_name(::std::string_view name) { _name = name; }
	auto&& get_name()const { return _name; }

	void set_stage(::vk::ShaderStageFlags stage) { _stage = stage; }
	auto&& get_stage()const { return _stage; }

	auto&& get_module()const { return _module; }

	constexpr NGS_CONFIG_STATIC_23 decltype(auto) operator()(VkPipelineShaderStageCreateInfo& info)
#if !defined(NGS_CPP_STANDARD_HAS_23)
		const
#endif
	{
		info.stage = static_cast<VkShaderStageFlagBits>(info.stage | static_cast<uint32_t>(_stage));
		info.module = _module;
		info.pName = _name.c_str();
		return info;
	}

private:
	::vk::Device _device{};
	VkShaderModule _module{};
	::std::string _name = "main";
	::vk::ShaderStageFlags _stage{};
};

template<flags::flag<::vk::ShaderStageFlagBits> _Stage>
struct stage_shader : shader
{
	NGS_MPL_ENVIRON(stage_shader);
public:
	stage_shader(::vk::Device device, ::std::ranges::contiguous_range auto&& code)
		: stage_shader(device, {
			reinterpret_cast<uint32_ptr_cst>(::std::ranges::data(NGS_PP_PERFECT_FORWARD(code))),
				sizeof(::std::ranges::range_value_t<decltype(code)>) * ::std::ranges::size(NGS_PP_PERFECT_FORWARD(code))
			}) {}
	stage_shader(::vk::Device device, ::std::span<const uint32_t> code) : stage_shader(device, ::vk::ShaderModuleCreateInfo({}, code.size(), code.data())) {}
	stage_shader(::vk::Device device, const VkShaderModuleCreateInfo& info)
		: base_type(device, info)
	{
		set_stage(static_cast<::vk::ShaderStageFlagBits>(static_cast<uint32_t>(_Stage)));
	}
};

namespace shaders {

	using vertex = stage_shader<::vk::ShaderStageFlagBits::eVertex>;
	using fragment = stage_shader<::vk::ShaderStageFlagBits::eFragment>;
	using geometry = stage_shader<::vk::ShaderStageFlagBits::eGeometry>;

	using tessellation_control = stage_shader<::vk::ShaderStageFlagBits::eTessellationControl>;
	using tessellation_evaluation = stage_shader<::vk::ShaderStageFlagBits::eTessellationEvaluation>;
}

NGS_LIB_END