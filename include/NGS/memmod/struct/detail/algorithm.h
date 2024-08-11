#pragma once

#include "./trait.h"
#include "./field_seq.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<structure T>
constexpr decltype(auto) field_size()
{
	return field_seq_trait<field_seq_t<T>>::size;
}

template<structure T, ::std::size_t Index>
	requires (Index < field_size<T>())
using struct_field_t = ::std::tuple_element_t<Index, typename field_seq_trait<field_seq_t<T>>::tuple_type>;

template<structure T>
constexpr ::std::size_t offset_of(::std::size_t index)
{
	return layouts::offset_of<fields::align_v<T>>(field_seq_trait<field_seq_t<T>>::sizes, index);
}



NGS_LIB_MODULE_END
