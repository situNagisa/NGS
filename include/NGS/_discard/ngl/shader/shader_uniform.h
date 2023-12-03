#pragma once

#include "NGS/ngl/shader/shader.h"

NGL_BEGIN
NGL_OBJ_BEGIN

template<CUniformTuple... _Tuples>
class NGS_DLL_API ShaderUniform : public Shader {
	NGS_MPL_ENVIRON(ShaderUniform);
public:
	using uniforms_type = uniforms_<_Tuples...>;
public:

	using base_type::base_type;
	constexpr ShaderUniform()
		: base_type(_Tuples::name.c_str()...)
	{}

	virtual void Update() override {
		if (!_required_update)return;
		base_type::Update();
		bind(this);
		((map::gl_set_uniform<typename _Tuples::element_type, _Tuples::element_count>(GetUniformLocation(std::string_view(_Tuples::name)), _GetPointer<_Tuples::name>())), ...);
	}
	/**
	 * \brief 获取对应变量
	 *
	 * \tparam _Id 变量名
	 *
	 * \note
	 *		该函数对模板元编程的依赖性极强，对编译器的要求也高，极有可能出现智能提示提示不出来的情况，
	 *		请确保变量名（模板参数_Id）没填错即可
	 *
	 * \return 当
	 *	`元素数量`为1时，若变量类型为矩阵，则返回一个`std::span`,若变量类型为基本类型，则返回基本类型的指针;
	 *  `元素数量`大于1时，返回一个`std::span`
	 */
	template<static_string _Id>
	constexpr auto GetUniform() {
		RequiredUpdate();
		return _uniforms.template Get<_Id>();
	}
	template<static_string _Id>
	void SetUniform(auto&& param) {
		GetUniform<_Id>() = std::forward<decltype(param)>(param);
	}

	friend std::string to_string(const self_type& shader) {
		return to_string(shader._uniforms);
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
		const auto span = GetUniform<_Tuple::name>();
		map::gl_set_uniform<typename _Tuple::element_type, _Tuple::element_count>(location, span.data());
	}
private:
	uniforms_type _uniforms{};
};

NGS_END
NGL_END
