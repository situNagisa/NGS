#pragma once

#include "./code.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	auto shader_creator()
	{
		contextes::context_t context;
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(context = ::glCreateProgram());
		return context;
	}
	void shader_deleter(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glDeleteProgram(context));
	}
	void shader_binder(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glUseProgram(context));
	}
	NGS_EXTERNAL_OPENGL_CONTEXT_DEFINE_BINDABLE_CONTEXT(basic_shader, _detail::shader_creator, _detail::shader_deleter, _detail::shader_binder);
}

struct context : _detail::basic_shader
{
	NGS_PP_INJECT(context);
public:
	using base_type::base_type;
	using base_type::operator=;

	template<auto Target>
	void attach(const code<Target>& code) const
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glAttachShader(self_type::get_handle(), code.get_handle()));
	}

	void link() const
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glLinkProgram(self_type::get_handle()));
#if NGS_BUILD_TYPE_IS_DEBUG
		//NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glValidateProgram(_context));
		::GLint status = GL_FALSE;
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glGetProgramiv(self_type::get_handle(), GL_LINK_STATUS, &status));
		if (status == GL_FALSE) {
			::GLint length;
			NGS_EXTERNAL_OPENGL_ERROR_CHECK(glGetProgramiv(self_type::get_handle(), GL_INFO_LOG_LENGTH, &length));
			NGS_ASSERT(length, "get length fail!");
			::std::string info(length, 0);
			NGS_EXTERNAL_OPENGL_ERROR_CHECK(glGetProgramInfoLog(self_type::get_handle(), length, &length, info.data()));
			NGS_ASSERT(false, fmt::c("link shader fail!\n %s", info.c_str()));
		}
#endif
	}

	::std::ptrdiff_t get_uniform_location(::std::string_view uniform_name) const
	{
		::std::ptrdiff_t result;
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(result = ::glGetUniformLocation(self_type::get_handle(), uniform_name.data()));
		return result;
	}

	void set_uniform(auto&&... args)const
		requires ::std::invocable<decltype(uniforms::set_uniform),decltype(args)...>
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(uniforms::set_uniform(NGS_PP_PERFECT_FORWARD(args)...));
	}
};

template<statics::strings::string Name, uniforms::uniform T, ::std::size_t Count = 1>
using pair = mpl::mstruct::named_pair<Name, T[Count]>;

template<class T>
concept shader_uniform = mpl::mstruct::named_field<T>;//&& uniforms::uniform<::std::ranges::range_value_t<mpl::mstruct::named_pair_field_t<T>>>;

template<shader_uniform... Uniforms>
struct shader
{
	NGS_PP_INJECT_BEGIN(shader);
public:
	using context_type = context;
	using struct_type = mpl::mstruct::named_struct<layout::default_align, Uniforms...>;

	explicit(false) shader(shader_code auto&&... codes)
	{
		((_context.attach(NGS_PP_PERFECT_FORWARD(codes))), ...);
		_context.link();

		contextes::bind(_context);

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