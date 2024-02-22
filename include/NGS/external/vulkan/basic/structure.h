#pragma once

#include "./flag.h"
#include "./defined.h"

NGS_LIB_BEGIN

using structure_t = ::vk::StructureType;

struct vulkan_struct
{
	structure_t type;
	void_ptr_cst next = nullptr;
	flag_t flags{};
};

#define NGS_EXTERNAL_VULKAN_STRUCT_BEGIN(vulkan_cxx_type)	\
structure_t type = vulkan_cxx_type::structureType;			\
void_ptr_cst next = nullptr;								\
flag_t flags{}												\
//

#define NGS_EXTERNAL_VULKAN_STRUCT(id)		\
using vulkan_type = Vk##id;					\
NGS_EXTERNAL_VULKAN_STRUCT_BEGIN(::vk::id)	\
//

NGS_LIB_END