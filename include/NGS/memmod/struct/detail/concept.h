#pragma once

#include "./trait.h"
#include "./field_seq.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept partial_structure = field_sequence<field_seq_t<T>> && layouts::align_policy<decltype(align_policy_v<T>)>;

template<class T>
concept structure = fields::field<T> && partial_structure<T>;

template<class T>
concept pure_field = fields::field<T> && !structure<T>;

NGS_LIB_MODULE_END


template<NGS_LIB_FULL_QUALIFIER_NAME::NGS_LIB_MODULE_NAME::partial_structure T>
struct NGS_NS::memmod::fields::align<T>
{
	constexpr static auto value =
		NGS_NS::memmod::layouts::align_of<
		NGS_LIB_FULL_QUALIFIER_NAME::NGS_LIB_MODULE_NAME::align_policy_v<T>
	>(
		NGS_LIB_FULL_QUALIFIER_NAME::NGS_LIB_MODULE_NAME::field_seq_trait<NGS_LIB_FULL_QUALIFIER_NAME::NGS_LIB_MODULE_NAME::field_seq_t<T>>::aligns
	);
};

template<NGS_LIB_FULL_QUALIFIER_NAME::NGS_LIB_MODULE_NAME::partial_structure T>
struct NGS_NS::memmod::fields::size<T>
{
	constexpr static auto value = 
		NGS_NS::memmod::layouts::size_of<NGS_NS::memmod::fields::align_v<T>>(
			NGS_LIB_FULL_QUALIFIER_NAME::NGS_LIB_MODULE_NAME::field_seq_trait<NGS_LIB_FULL_QUALIFIER_NAME::NGS_LIB_MODULE_NAME::field_seq_t<T>>::sizes
		);
};