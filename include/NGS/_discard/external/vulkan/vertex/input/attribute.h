#pragma once

#include "../../tvm.h"
#include "../../info.h"
#include "./defined.h"

NGS_EXTERNAL_VULKAN_INFO_ENVIRONMENT(VertexInputAttributeDescription);
NGS_LIB_MODULE_BEGIN

template<class _Type>
struct attribute
{
	using variable_type = mpl::mstruct::variable<_Type>;

	constexpr static auto format = tvm::format::value<tvm::adapter_t<typename variable_type::storage_type>>;

	constexpr NGS_CONFIG_STATIC_23 decltype(auto) operator()(VkVertexInputAttributeDescription& info)
#if !defined(NGS_CPP_STANDARD_HAS_23)
		const
#endif
	{
		info.format = static_cast<VkFormat>(format);
		return info;
	}
};

template<class _T, class _O = type_traits::object_t<_T>>
concept CAttribute = requires
{
	{ _O::format } -> ::std::convertible_to<::vk::Format>;
	requires ::std::invocable<_T, VkVertexInputAttributeDescription&>;
	requires mpl::mstruct::CVariable<typename _O::variable_type>;
};


NGS_LIB_MODULE_END