#pragma once

#include "./basic_address.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct visual_address : basic_address
{
	NGS_MPL_ENVIRON(visual_address);
public:
	constexpr explicit(true) visual_address(typename base_type::underlying_type value)
		: base_type(value)
	{}
	constexpr explicit(false) visual_address(const void* ptr) : base_type(reinterpret_cast<base_type::underlying_type>(ptr)) {}

	template<class T> requires ::std::is_object_v<T>
	explicit(false) operator T* () const
	{
		return reinterpret_cast<T*>(base_type::value());
	}
};

NGS_LIB_MODULE_END