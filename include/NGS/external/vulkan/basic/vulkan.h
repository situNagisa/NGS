#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<class _T> requires requires{ typename type_traits::object_t<_T>::vulkan_type; }
using vulkan_info_t = typename type_traits::object_t<_T>::vulkan_type;

template<class _T>
concept vulkan_layout_info = requires { typename vulkan_info_t<_T>; } && (alignof(_T) == alignof(vulkan_info_t<_T>)) && (sizeof(_T) == sizeof(vulkan_info_t<_T>));

template<class _T>
concept vulkan_member_info = requires(_T t) { { NGS_PP_PERFECT_FORWARD(t).to_vulkan() }; };

template<class _T>
concept vulkan_info = vulkan_layout_info<_T> || vulkan_member_info<_T>;

inline constexpr struct
{
	decltype(auto) operator()(vulkan_info auto&& info)const
	{
		using vulkan_type = vulkan_info_t<decltype(info)>;
		if constexpr (vulkan_member_info<decltype(info)>)
		{
			return NGS_PP_PERFECT_FORWARD(info).to_vulkan();
		}
		else if constexpr (vulkan_layout_info<decltype(info)>)
		{
			return *reinterpret_cast<const vulkan_type*>(&info);
		}
		else
		{
			static_assert(cpt::none<decltype(info)>, "invalid vulkan_info");
		}
	}
}to_vulkan{};

NGS_LIB_END