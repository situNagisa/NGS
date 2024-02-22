#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

NGS_TVM_TV_REGISTER(format, ::vk::Format);

#define NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP(type,bit,suffix)								\
NGS_TVM_TV_INSERT(format, type, ::vk::Format::eR##bit##suffix);							\
NGS_TVM_TV_INSERT(format, type[1], ::vk::Format::eR##bit##suffix);						\
NGS_TVM_TV_INSERT(format, type[2], ::vk::Format::eR##bit##G##bit##suffix);				\
NGS_TVM_TV_INSERT(format, type[3], ::vk::Format::eR##bit##G##bit##B##bit##suffix);		\
NGS_TVM_TV_INSERT(format, type[4], ::vk::Format::eR##bit##G##bit##B##bit##A##bit##suffix)	\
//

NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP(uint8, 8, Uint);
NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP(uint16, 16, Uint);
NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP(uint32, 32, Uint);
NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP(uint64, 64, Uint);

NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP(int8, 8, Sint);
NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP(int16, 16, Sint);
NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP(int32, 32, Sint);
NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP(int64, 64, Sint);

NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP(float32, 32, Sfloat);
NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP(float64, 64, Sfloat);

#undef NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP

NGS_LIB_MODULE_END