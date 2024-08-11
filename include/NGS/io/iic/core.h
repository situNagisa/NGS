#pragma once

#include "./detail.h"
#include "./defined.h"

NGS_LIB_BEGIN

using details::ack;

using details::address_width;
using details::address_io;
using details::address;
using details::address_cast;

using details::iic_value;
using details::iic_value_t;
using details::iic_address_width;
using details::iic_address_width_v;
using details::write;
using details::read;
using details::connect;
using details::current_address;
using details::iic_address_t;
using details::ack_policy;

using details::master;
using details::slave;
using details::iic;
using details::input_iic;
using details::output_iic;
using details::input_and_output_iic;
using details::input_or_output_iic;

using details::write_range;
using details::read_range;

NGS_LIB_END