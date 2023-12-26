#pragma once

#define NGS_BASIC_HAS_PROPERTY(type,property,property_type)	::std::same_as<decltype(type::property),property_type>
#define NGS_BASIC_HAS_PROPERTY_OBJECT(object,property,property_type)	::std::same_as<decltype(::std::remove_cvref_t<decltype(object)>::property),property_type>

#define NGS_BASIC_PROPERTY_CONVERTIBLE(type,property,aim_type)	::std::convertible_to<decltype(type::property),aim_type>
#define NGS_BASIC_PROPERTY_CONVERTIBLE_OBJECT(object,property,aim_type)	::std::convertible_to<decltype(::std::remove_cvref_t<decltype(object)>::property),aim_type>