#pragma once

#include "./attribute.h"

NGS_EXTERNAL_VULKAN_INFO_ENVIRONMENT(VertexInputBindingDescription);
NGS_LIB_MODULE_BEGIN

template<class _T, class _O = type_traits::object_t<_T>>
concept CBinder = requires(_O f, size_t vertex_count)
{
	{ _O::attribute_count } -> ::std::convertible_to<size_t>;
	{ _O::formats } -> ::std::convertible_to<::std::array<::vk::Format, _O::attribute_count>>;
	{ f(vertex_count) } -> ::std::invocable<VkBufferCreateInfo&>;
		requires ::std::invocable<_T, ::std::span<VkVertexInputAttributeDescription>>;
		requires ::std::invocable<_T, VkVertexInputBindingDescription&>;
		requires mpl::mstruct::CStructure<typename _O::structure_type>;
};

namespace detail {

	template<CAttribute... _Attributes>
	struct binder
	{
		using structure_type = mpl::mstruct::structure<typename _Attributes::variable_type...>;
		constexpr static size_t attribute_count = sizeof...(_Attributes);
		constexpr static ::std::array<::vk::Format, attribute_count> formats = { _Attributes::format... };

		constexpr NGS_CONFIG_STATIC_23::std::span<VkVertexInputAttributeDescription> operator()(::std::span<VkVertexInputAttributeDescription> infos)
#if !defined(NGS_CPP_STANDARD_HAS_23)
			const
#endif
		{
			[infos] <size_t... _Index>(::std::index_sequence<_Index...>) {
				((
					_Attributes{}(infos[_Index]),
					infos[_Index].location = static_cast<uint32_t>(_Index),
					infos[_Index].offset = static_cast<uint32_t>(structure_type::get_variables()[_Index].offset)
					), ...);
			}(::std::make_index_sequence<attribute_count>());
			return infos;
		}

		constexpr NGS_CONFIG_STATIC_23 VkVertexInputBindingDescription& operator()(VkVertexInputBindingDescription& info)
#if !defined(NGS_CPP_STANDARD_HAS_23)
			const
#endif
		{
			info.stride = static_cast<uint32_t>(structure_type::size);
			return info;
		}

		constexpr NGS_CONFIG_STATIC_23 auto operator()(size_t vertex_count)
#if !defined(NGS_CPP_STANDARD_HAS_23)
			const
#endif
		{
			return [=](VkBufferCreateInfo& info) -> VkBufferCreateInfo&
				{
					info.size = static_cast<uint32_t>(structure_type::size * vertex_count);
					info.usage |= static_cast<VkBufferUsageFlags>(::vk::BufferUsageFlagBits::eVertexBuffer);
					return info;
				};
		}
	};

	template<class...>struct make_binder;

	/// @brief 
	///
	template<class... _Types> using make_binder_t = typename make_binder<_Types...>::type;

	template<class... _Types>
	struct make_binder
	{
		using type = binder<
			::std::conditional_t<CAttribute<_Types>, _Types, attribute<_Types>>...
		>;
	};
}

template<class... _Types> using binder = detail::make_binder_t<_Types...>;
template<class... _Types> using binder_c = binder< _Types...>;

NGS_LIB_MODULE_END