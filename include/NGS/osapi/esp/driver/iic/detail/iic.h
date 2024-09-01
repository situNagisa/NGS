#pragma once

#include "./master.h"
#include "./slave.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::copyable Value = ::std::uint8_t>
	requires ::std::is_standard_layout_v<Value>
struct iic_master : esp_iic_master
{
	NGS_PP_INJECT(iic_master);
public:
	using value_type = Value;
	using address_type = ::std::uint16_t;

	using base_type::base_type;

	void connect(address_type address)
	{
		_address = address;
	}



	address_type _address;
};

NGS_LIB_MODULE_END