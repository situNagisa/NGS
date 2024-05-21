#pragma once

#include "../reflect.h"
#include "./shader.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<statics::strings::string Name,valid_fundamental T>
using uniform = mpl::mstruct::named_pair<Name, T>;

template<class T>
concept shader_uniform = mpl::mstruct::named_field<T>;

template<shader_uniform... Uniforms>
struct uniform_shader : shader
{
	NGS_PP_INJECT(uniform_shader);
public:
	using struct_type = mpl::mstruct::named_struct<layout::default_align, Uniforms...>;

	explicit(false) uniform_shader(_detail::glsl auto&&... glsl)
		: base_type(NGS_PP_PERFECT_FORWARD(glsl)...)
	{
		_locations.reserve(sizeof...(Uniforms));

		((_locations[mpl::mstruct::named_pair_name_t<Uniforms>::value] = base_type::get_uniform_location(mpl::mstruct::named_pair_name_t<Uniforms>::value)), ...);
	}

	void set_uniform(::std::string_view name, const ::std::ranges::contiguous_range auto& data, ::std::ptrdiff_t offset = 0)
		requires algorithm::_detail::uniform<::std::ranges::range_value_t<decltype(data)>>
	{
		base_type::set_uniform(_locations.at(name), data, offset);
	}
	void set_uniform(::std::string_view name, const algorithm::_detail::uniform auto& data)
		requires algorithm::_detail::fundametal_uniform<::std::ranges::range_value_t<decltype(data)>>
	{
		base_type::set_uniform(_locations.at(name), data);
	}

	using base_type::operator=;

	::std::unordered_map<::std::string_view, ::std::ptrdiff_t> _locations{};
	struct_type _struct;
};

NGS_LIB_MODULE_END