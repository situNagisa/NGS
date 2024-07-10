#pragma once

#include "../basic.h"
#include "./glsl.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<statics::strings::string Name, NGS_EXTERNAL_OPENGL_BASIC_UNIFORM_NS::uniform T, ::std::size_t Count = 1>
using pair = mpl::mstruct::named_pair<Name, T[Count]>;

template<class T>
concept shader_uniform = mpl::mstruct::named_field<T>;//&& uniforms::uniform<::std::ranges::range_value_t<mpl::mstruct::named_pair_field_t<T>>>;

namespace _detail
{
	template <auto Args>
	void derived_from_basic_glsl(const basic_glsl<Args>&);

	template <class T>
	concept glsl = requires(const T & obj) { _detail::derived_from_basic_glsl(obj); };
}

template<shader_uniform... Uniforms>
struct shader
{
	NGS_PP_INJECT_BEGIN(shader);
public:
	using context_type = NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::shader;
	using struct_type = mpl::mstruct::named_struct<layout::default_align, Uniforms...>;

	explicit(false) shader(_detail::glsl auto&&... glsl)
	{
		((_context.attach(glsl.get_context())), ...);
		_context.link();

		NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::bind(_context);

		_locations.reserve(sizeof...(Uniforms));

		((_locations[mpl::mstruct::named_pair_name_t<Uniforms>::value] = _context.get_uniform_location(mpl::mstruct::named_pair_name_t<Uniforms>::value)), ...);
	}

	[[nodiscard]] constexpr auto&& get_context()const { return _context; }

	template<statics::strings::string Name>
	using _uniform_type = mpl::mstruct::variable_value_t<mpl::mstruct::named_field_at_t<struct_type, Name>>;

	template<statics::strings::string Name>
	constexpr static auto _is_one_dimension_uniform() { return ::std::extent_v<_uniform_type<Name>> == 1; }

	template<statics::strings::string Name>
	using _param_type = ::std::conditional_t<_is_one_dimension_uniform<Name>(), ::std::ranges::range_value_t<_uniform_type<Name>>, ::std::span<::std::ranges::range_value_t<_uniform_type<Name>>>>;

	template<statics::strings::string Name>
	void set_uniform(const _param_type<Name>& args)const
	{
		if constexpr (_is_one_dimension_uniform<Name>())
		{
			_context.set_uniform(_locations.at(Name), ::std::span{ &args,1 });
		}
		else
		{
			_context.set_uniform(_locations.at(Name), args);
		}
	}

	context_type _context;
	::std::unordered_map<::std::string_view, ::std::ptrdiff_t> _locations{};
};

NGS_LIB_MODULE_END