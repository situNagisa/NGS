#pragma once

#include "../defined.h"

NGS_LIB_MODULE_BEGIN

template<mpl::mstruct::CFlattenedStructure _LocationStruct, size_t... _ActiveIndices>
	requires ((_ActiveIndices < _LocationStruct::variable_count) && ...)
struct buffer_binder
{
	using location_struct = _LocationStruct;
	constexpr static size_t attribute_count = sizeof...(_ActiveIndices);
	constexpr static std::array<size_t, attribute_count> active_indices = { _ActiveIndices... };

	constexpr static auto get_description()
	{
		vk::VertexInputBindingDescription description{};

		return description;
	}
};

NGS_LIB_MODULE_END