#pragma once

#include "./ack.h"
#include "./address.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

NGS_TCEA_TRAIT_DEFAULT_TYPE(iic_value, ::std::byte);
NGS_TCEA_TRAIT_ALIAS_T(iic_value);
NGS_TCEA_TRAIT_HAS_TYPE_OBJECT(iic_value, value_type);

NGS_TCEA_TRAIT_DEFAULT_VALUE(iic_address_width, 0);
NGS_TCEA_TRAIT_ALIAS_V(iic_address_width);
NGS_TCEA_TRAIT_HAS_VALUE_OBJECT(iic_address_width, address_width);

NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(write, (::std::convertible_to<iic_value_t<T>>));
NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(read, (::std::convertible_to<iic_value_t<T>>));

NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(connect, (address<iic_address_width_v<T>>));
NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(current_address);
NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(ack_policy, (::std::convertible_to<ack>));

template<class T>
using _iic_address_t = ::std::invoke_result_t<decltype(current_address), T>;

NGS_TCEA_TRAIT_DEFAULT_TYPE(iic_address, _iic_address_t<T>);
NGS_TCEA_TRAIT_ALIAS_T(iic_address);
NGS_TCEA_TRAIT_HAS_TYPE_OBJECT(iic_address, address_type);


NGS_LIB_MODULE_END