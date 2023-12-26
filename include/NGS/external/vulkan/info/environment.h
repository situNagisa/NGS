#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

#define NGS_EXTERNAL_VULKAN_INFO_PROP_ASSIGN(function,info_type,param_type,property)\
constexpr auto function(param_type param)									\
	{																		\
		return[=](info_type& info) -> info_type&							\
		{																	\
			info.property = static_cast<decltype(info.property)>(param);	\
			return info;													\
		};																	\
	}																		\
//

template<class _T> struct info_creator { using type = _T; };
template<class _T> using info_creator_t = typename info_creator<_T>::type;
//sb vulkan cpp api,qnmd
template<class _T>
constexpr auto create_info()
{
	_T result{};
	info_creator_t<_T> creator{};
	if constexpr (requires{ result.sType = static_cast<decltype(result.sType)>(creator.sType); })
	{
		result.sType = static_cast<decltype(result.sType)>(creator.sType);
	}
	if constexpr (requires{ result.pNext = static_cast<decltype(result.pNext)>(creator.pNext); })
	{
		result.pNext = static_cast<decltype(result.pNext)>(creator.pNext);
	}
	if constexpr (requires{ result.flags = static_cast<decltype(result.flags)>(creator.flags); })
	{
		result.flags = static_cast<decltype(result.flags)>(creator.flags);
	}
	return result;
}

inline constexpr struct evaluate_t {} evaluate{};

#define NGS_EXTERNAL_VULKAN_INFO_REGISTER(key,value) template<> struct NGS_ external::vk:: info_creator<key> { using type = value; }
#define NGS_EXTERNAL_VULKAN_INFO_REGISTER_DEFAULT(name) NGS_EXTERNAL_VULKAN_INFO_REGISTER(Vk##name,::vk::name)

#define NGS_EXTERNAL_VULKAN_INFO_OPERATOR(type)															\
constexpr decltype(auto) operator|(::std::invocable<type&> auto&& l, ::std::invocable<type&> auto&& r)	\
{																										\
	constexpr bool l_ref = ::std::is_lvalue_reference_v<decltype(l)>;									\
	constexpr bool r_ref = ::std::is_lvalue_reference_v<decltype(r)>;									\
	if constexpr (l_ref && r_ref)																		\
	{																									\
		return [&](type& info) -> type&	{ l(info);	r(info); return info;};								\
	}																									\
	if constexpr (l_ref && !r_ref)																		\
	{																									\
		return [&l, r](type& info) -> type&	{ l(info);	r(info); return info;};							\
	}																									\
	if constexpr (!l_ref && r_ref)																		\
	{																									\
		return [l, &r](type& info) -> type&	{ l(info);	r(info); return info;};							\
	}																									\
	if constexpr (!l_ref && !r_ref)																		\
	{																									\
		return [=](type& info) -> type&	{ l(info);	r(info); return info;};								\
	}																									\
}																										\
constexpr decltype(auto) operator|(::std::invocable<::std::span<type>> auto&& l, ::std::invocable<::std::span<type>> auto&& r)\
{																										\
	constexpr bool l_ref = ::std::is_lvalue_reference_v<decltype(l)>;									\
	constexpr bool r_ref = ::std::is_lvalue_reference_v<decltype(r)>;									\
	if constexpr (l_ref && r_ref)																		\
	{																									\
		return [&](type& info) -> type&	{ l(info);	r(info); return info;};								\
	}																									\
	if constexpr (l_ref && !r_ref)																		\
	{																									\
		return [&l, r](type& info) -> type&	{ l(info);	r(info); return info;};							\
	}																									\
	if constexpr (!l_ref && r_ref)																		\
	{																									\
		return [l, &r](type& info) -> type&	{ l(info);	r(info); return info;};							\
	}																									\
	if constexpr (!l_ref && !r_ref)																		\
	{																									\
		return [=](type& info) -> type&	{ l(info);	r(info); return info;};								\
	}																									\
}																										\
constexpr decltype(auto) operator|(::std::invocable<type&> auto&& f,NGS_NS::NGS_EXTERNAL_VULKAN_NS::evaluate_t) {\
	auto result = NGS_NS::NGS_EXTERNAL_VULKAN_NS::create_info<type>();									\
	f(result);																							\
	return result;																						\
}																										\
constexpr decltype(auto) operator|=(type& info, ::std::invocable<type&> auto&& f) { return f(info); }	\
constexpr decltype(auto) operator|=(::std::span<type> infos, ::std::invocable<::std::span<type>> auto&& f) { return f(infos); }	\
//


#define NGS_EXTERNAL_VULKAN_INFO_ENVIRONMENT(name)	\
NGS_LIB_BEGIN										\
NGS_EXTERNAL_VULKAN_INFO_REGISTER_DEFAULT(name);	\
NGS_LIB_END											\
NGS_EXTERNAL_VULKAN_INFO_OPERATOR(Vk##name)			\
//

NGS_LIB_END