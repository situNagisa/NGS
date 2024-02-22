#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

NGS_TVM_TV_REGISTER(format, vk::Format);

#define NGS_EXTERNAL_VULKAN_FORMAT_TV_MAP(type,bit,suffix)								\
NGS_TVM_TV_INSERT(format, type, vk::Format::eR##bit##suffix);							\
NGS_TVM_TV_INSERT(format, type[1], vk::Format::eR##bit##suffix);						\
NGS_TVM_TV_INSERT(format, type[2], vk::Format::eR##bit##G##bit##suffix);				\
NGS_TVM_TV_INSERT(format, type[3], vk::Format::eR##bit##G##bit##B##bit##suffix);		\
NGS_TVM_TV_INSERT(format, type[4], vk::Format::eR##bit##G##bit##B##bit##A##bit##suffix)	\
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

template<class _T>
struct adapter
{
	using type = _T;
};

template<cpt::fundamental _T> requires !::std::ranges::contiguous_range<_T>
struct adapter<_T>
{
	using type = _T;
};

template<std::ranges::contiguous_range _Range>
struct adapter<_Range>
{
	using range_type = _Range;
	using value_type = type_traits::naked_t<std::ranges::range_value_t<_Range>>;
	using type = value_type[sizeof(_Range) / sizeof(value_type)];
};

template<class _T>
using adapter_t = typename adapter<_T>::type;


NGS_LIB_MODULE_END