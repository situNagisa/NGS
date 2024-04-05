#pragma once

#include "../basic.h"
#include "./shader.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
	template<cpt::derived_from_specialization<shader> Shader>
struct uniform_memory
{
	NGS_MPL_ENVIRON_BEGIN(uniform_memory);
public:
	using shader_type = Shader;
	using struct_type = typename shader_type::struct_type;

	explicit(false) uniform_memory(const shader_type& shader) : _shader(::std::cref(shader)) {}

	template<statics::strings::string Name>
	static decltype(auto) _get(auto&& s)
	{
		using value_type = mpl::mstruct::variable_value_t<mpl::mstruct::named_field_at_t<struct_type, Name>>;
		static_assert(::std::is_bounded_array_v<value_type>);
		if constexpr (::std::extent_v<value_type> == 1)
		{
			return mpl::mstruct::get<Name>(NGS_PP_PERFECT_FORWARD(s))[0];
		}
		else
		{
			return mpl::mstruct::get<Name>(NGS_PP_PERFECT_FORWARD(s));
		}
	}

	template<statics::strings::string Name>
	decltype(auto) get() { return self_type::template _get<Name>(_struct); }
	template<statics::strings::string Name>
	decltype(auto) get() const { return self_type::template _get<Name>(_struct); }

	template<statics::strings::string Name>
	static decltype(auto) _set(const shader_type& shader, auto&& s,auto&& arg)
	{
		shader.template set_uniform<Name>(self_type::template _get<Name>(NGS_PP_PERFECT_FORWARD(s)) = NGS_PP_PERFECT_FORWARD(arg));
	}

	template<statics::strings::string Name>
	void set(auto&& arg) requires ::std::assignable_from<decltype(self_type::template _get<Name>(::std::declval<struct_type>())),decltype(arg)>
	{
		self_type::template _set<Name>(_shader, _struct, NGS_PP_PERFECT_FORWARD(arg));
	}

	template<statics::strings::string Name>
	void _submit()const
	{
		_shader.get().template set_uniform<Name>(this->template get<Name>());
	}

	template<statics::strings::string... Name>
	void submit() const
	{
		NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::bind(_shader.get().get_context());
		(_submit<Name>(), ...);
	}

	::std::reference_wrapper<const shader_type> _shader;
	struct_type _struct;
};

template<cpt::derived_from_specialization<shader> Shader>
uniform_memory(const Shader&) -> uniform_memory<Shader>;

NGS_LIB_MODULE_END