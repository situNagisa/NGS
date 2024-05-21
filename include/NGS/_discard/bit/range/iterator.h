#pragma once

#include "../bitset.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct bit_wrapper
{
	
};


template<>
struct bit_iterator : ::boost::stl_interfaces::iterator_interface<bit_iterator, ::std::random_access_iterator_tag, bool>
{

};

NGS_LIB_MODULE_END