#pragma once

#include "../defined.h"

NGS_LIB_MODULE_BEGIN

template<class _Type>
struct attribute
{
	using description_type = vk::VertexInputAttributeDescription;
	using variable_type = mpl::mstruct::variable<_Type>;

	constexpr attribute() = default;

	constexpr auto get_description()const
	{
		description_type description{};



		return description;
	}


};

NGS_LIB_MODULE_END