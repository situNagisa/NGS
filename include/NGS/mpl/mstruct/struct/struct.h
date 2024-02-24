#pragma once

#include "../variable.h"
#include "../basic.h"
#include "./descriptor.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<layout::align Align, class... Ts>
struct alignas(basic::struct_align_v<basic::meta_struct<Align, Ts...>>) opaque_struct_mirror : basic::meta_struct<Align,Ts...>
{
	NGS_MPL_ENVIRON2(opaque_struct_mirror, basic::meta_struct<Align, Ts...>);
public:

	byte _data[basic::struct_size_v<base_type>]{};
};

template<::std::size_t Index>
constexpr decltype(auto) get(storage_structure auto&& s) requires (Index < basic::struct_size_v<struct_descriptor_t<decltype(s)>>)
{
	using field_type = variables::variable_value_t<basic::field_at_t<struct_descriptor_t<decltype(s)>, Index>>;
	auto ptr = reinterpret_cast<type_traits::add_cv_like_t<decltype(s),byte_ptr>>(::std::addressof(NGS_PP_PERFECT_FORWARD(s))) + basic::field_offset_v<struct_descriptor_t<decltype(s)>, Index>;
	return *reinterpret_cast<type_traits::add_cv_like_t<decltype(s),field_type*>>(ptr);
}

NGS_LIB_MODULE_END
