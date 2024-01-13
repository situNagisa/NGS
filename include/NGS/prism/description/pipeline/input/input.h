#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct vertex_input
{
private:
	using binding_type = uint32_t;
	using stride_type = uint32_t;
	using location_type = uint32_t;
	using offset_type = uint32_t;
	enum class rate_type
	{
		vertex,
		instance,
	};
	enum class format_type
	{
		undefined,
	};

	struct binding_description
	{
		binding_type binding = 0;
		stride_type stride = 0;
		rate_type input_rate = rate_type::vertex;
	};
	struct attribute_description
	{
		location_type location = 0;
		binding_type binding = 0;
		format_type format = format_type::undefined;
		offset_type offset = 0;
	};
public:
	::std::span<binding_description> bindings{};
	::std::span<attribute_description> attributes{};
};

NGS_LIB_MODULE_END