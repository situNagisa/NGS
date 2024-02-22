#pragma once

#include "./structure.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<class>
struct trait;

template<class _T>
concept vulkan_trait = requires
{
	typename type_traits::object_t<_T>::info_type;
	typename type_traits::object_t<_T>::entity_type;
	{ type_traits::object_t<_T>::structure_type } -> ::std::convertible_to<structure_t>;
};


NGS_LIB_END

#define NGS_EXTERNAL_VULKAN_REGISTER_MODULE(				\
	module_name,											\
	info_type_,												\
	entity_type_,											\
	structure_type_,										\
	create_functor_,										\
	destroy_functor_										\
)															\
NGS_LIB_MODULE_BEGIN										\
struct tag{};												\
NGS_LIB_MODULE_END											\
NGS_LIB_BEGIN												\
using module_name##_tag = NGS_LIB_MODULE_NAME::tag;			\
template<>													\
struct trait<module_name##_tag>								\
{															\
	using info_type = info_type_;							\
	using entity_type = entity_type_;						\
	constexpr static auto structure_type = structure_type_;	\
	constexpr static auto create_functor = create_functor_;	\
	constexpr static auto destroy_functor = destroy_functor_;\
};															\
using module_name##_trait = trait<module_name##_tag>;		\
NGS_LIB_END													\
NGS_LIB_MODULE_BEGIN										\
using trait = module_name##_trait;							\
NGS_LIB_MODULE_END											\
//