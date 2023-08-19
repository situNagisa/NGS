#pragma once

#include "NGS/ngl/shader/shader.h"

NGL_BEGIN
NGL_OBJ_BEGIN

template<CUniformTuple... _Tuples>
class NGS_API ShaderUniform : public Shader {
	NGS_menvironment(ShaderUniform);
public:
	using uniforms_type = uniforms_<_Tuples...>;

	using base_type::base_type;
	constexpr ShaderUniform()
		: base_type(_Tuples::name.c_str()...)
	{}

	virtual void Update() override {
		if (!_required_update)return;
		base_type::Update();
		OpenGL::I().shader->Select(this);
		((map::gl_set_uniform<typename _Tuples::original_type, _Tuples::dimension, _Tuples::element_count>(GetUniformLocation(std::string_view(_Tuples::name)), _GetPointer<_Tuples::name>())), ...);
	}
	template<static_string _Id>
	constexpr auto Get() {
		RequiredUpdate();
		return _uniforms.template Get<_Id>();
	}
private:
	template<static_string _Id>
	constexpr auto _GetPointer() {
		return _uniforms.template GetPointer<_Id>();
	}
private:
	template<CUniformTuple _Tuple>
	void _UpdateUniform() {
		const auto location = GetUniformLocation(std::string_view(_Tuple::name));
		const auto span = Get<_Tuple::name>();
		map::gl_set_uniform<typename _Tuple::original_type, _Tuple::dimension, _Tuple::element_count>(location, span.data());
	}
private:
	uniforms_type _uniforms{};
};

NGS_END
NGL_END
