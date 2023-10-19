#pragma once

#include "./shader.h"
#include "./glsl/uniform.h"

NGL_BEGIN
NGL_OBJ_BEGIN

template<mpl::mstruct::CPair... _Pairs>
class NGS_API ShaderUniform : public Shader {
	NGS_MPL_ENVIRON(ShaderUniform);
public:
	using uniforms_type = mpl::mstruct::name_struct<layout::no_align_t, _Pairs...>;
public:

	using base_type::base_type;
	constexpr ShaderUniform()
		: base_type(_Pairs::first_type::value.data()...)
	{}

	virtual void Update() override {
		if (!_required_update)return;
		base_type::Update();
		bind(this);
		((
			map::gl_set_uniform<
			typename mpl::mstruct::variable_traits<typename mpl::mstruct::variable_at_key<uniforms_type, typename _Pairs::first_type>::type>::element_type,
			mpl::mstruct::variable_traits<typename mpl::mstruct::variable_at_key<uniforms_type, typename _Pairs::first_type>::type>::element_count
			>(
				GetUniformLocation(_Pairs::first_type::value.data()),
				_GetPointer<_Pairs::first_type::value>()
			)), ...);
	}
	
	template<static_strings::static_string _Id>
	constexpr auto&& GetUniform() {
		RequiredUpdate();
		return _uniforms.template get<_Id>();
	}
	template<static_strings::static_string _Id>
	void SetUniform(auto&& param) {
		if constexpr (requires{GetUniform<_Id>() = std::forward<decltype(param)>(param); }) {
			GetUniform<_Id>() = std::forward<decltype(param)>(param);
		}
		else if constexpr (
			mpl::mstruct::variable_traits<boost::fusion::result_of::value_at_key<typename uniforms_type::map_type, mpl::mstruct::variable_id<_Id>>>::is_range
			&& std::ranges::input_range<decltype(param)>
			) {
			std::ranges::copy(std::forward<decltype(param)>(param), std::ranges::begin(GetUniform<_Id>()));
		}
		else {
			static_assert(ccpt::None<mpl::mstruct::variable_id<_Id>>, "the value type is not support assign");
		}
	}

	friend std::string to_string(const self_type& shader) {
		return to_string(shader._uniforms);
	}
private:
	template<static_strings::static_string _Id>
	constexpr auto _GetPointer() {
		return &_uniforms.template get<_Id>();
	}
private:
	uniforms_type _uniforms{};
};

NGS_END
NGL_END
