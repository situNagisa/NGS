#pragma once

#include "./shader.h"

NGS_LIB_BEGIN

NGS_HPP_INLINE shader::shader(::vk::Device device, const VkShaderModuleCreateInfo& info)
	: _device(device)
	, _module(device.createShaderModule(info))
{

}

NGS_HPP_INLINE shader::~shader()
{
	_device.destroyShaderModule(_module);
}

NGS_LIB_END
