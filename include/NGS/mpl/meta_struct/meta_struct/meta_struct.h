#pragma once

#include "NGS/mpl/meta_struct/meta_struct/variable_adapter.h"

NGS_MPL_BEGIN

template<class _MetaStruct = void>
concept CMetaStruct = requires() {
	{ _MetaStruct::count } -> std::convertible_to<size_t>;
	{ _MetaStruct::size } -> std::convertible_to<size_t>;
	{ _MetaStruct::variables } -> std::convertible_to<std::array<meta_variable_d, _MetaStruct::count>>;

		requires CMetaVariable<typename _MetaStruct::template variable_at<0>>;
		requires CVector<typename _MetaStruct::variable_types>;
};

NGS_mfunction(meta_struct, class ...);
NGS_mfunction(meta_struct, _CVariableAdapter... _Adapters) < _Adapters... > {
private:
	using _adapters = vector<_Adapters...>;
	template<size_t _Index> using _adapters_at = typename _adapters::template at_c<_Index>;
public:
	NGS_mcst_t variable_types = vector<typename _Adapters::variable_type...>;

	/** @brief 第n个元变量 */
	template<size_t _Index>
	NGS_mcst_t variable_at = typename _adapters_at<_Index>::variable_type;

	/** @brief 元变量个数 */
	NGS_mcst size_t count = _adapters::size;
	/** @brief 元结构体大小 */
	NGS_mcst size_t size = (0 + ... + _Adapters::variable_type::size);

private:
	NGS_mcst std::array<size_t, count> _sizes = { { _Adapters::variable_type::size... } };
	consteval static size_t _GET_OFFSET(size_t index) { return index ? _GET_OFFSET(index - 1) + _sizes[index - 1] : 0; }
	template<size_t _Index>
	NGS_mcst size_t _offset = _GET_OFFSET(_Index);
public:
	/** @brief 元变量对应的动态结构体数组（可动态访问） */
	NGS_mcst std::array<meta_variable_d, count> variables = { meta_variable_d{_Adapters::variable_type::element_count, _Adapters::variable_type::size,_offset<_Adapters::index>, }... };
private:
	byte _data[size];
};

//================
// factory
//================

NGS_mfunction(_transform_to_variable, class _Type) {
	using result_type = std::conditional_t<CMetaVariable<_Type>, _Type, meta_variable_c<_Type, 1>>;
};
template<class _Type>
using _transform_to_variable_t = typename _transform_to_variable<_Type>::result_type;

NGS_mfunction(_make_meta_struct, class, class...);
NGS_mfunction(_make_meta_struct, class... _Variables, size_t... _Index) < std::index_sequence<_Index...>, _Variables... > {
	NGS_mcst_t result_type = meta_struct<_variable_adapter_c<_transform_to_variable_t<_Variables>, _Index > ... > ;
};
template<class... _Variables>
using _make_meta_struct_t = typename _make_meta_struct<std::index_sequence_for<_Variables...>, _Variables...>::result_type;

//================
// alias
//================

template<class... _Variables>
using meta_struct_c = _make_meta_struct_t<_Variables...>;

template<class... _Variables>
using struct_ = meta_struct_c<_Variables...>;

//================
// dynamic cache
//================

struct NGS_API meta_struct_d {
	size_t count;
	size_t size;
	std::span<const meta_variable_d> vars;
};

template<CMetaStruct _MetaStruct>
consteval meta_struct_d make_meta_struct() { return { _MetaStruct::count, _MetaStruct::size, _MetaStruct::variables }; }

NGS_CCPT_VERIFY(CMetaStruct, meta_struct_c<var_<int, 3>, var_<float, 13>>);

NGS_MPL_END
