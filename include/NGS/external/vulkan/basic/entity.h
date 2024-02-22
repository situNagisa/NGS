#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<vulkan_trait _Trait>
struct basic_entity : bases::delete_copy
{
	NGS_MPL_ENVIRON_BEGIN(basic_entity);
public:
	using trait_type = _Trait;
	using info_type = typename trait_type::info_type;
	using entity_type = typename trait_type::entity_type;

	constexpr basic_entity() = default;
	constexpr basic_entity(::std::convertible_to<entity_type> auto&& entity) : _entity(NGS_PP_PERFECT_FORWARD(entity)) {}

	constexpr auto&& value() { return _entity; }
	constexpr auto&& value()const { return _entity; }
private:
	entity_type _entity;
};


NGS_LIB_END
