#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/mpl/mpl_macro.h"
#include "NGS/base/mpl/concepts/concept.h"
#include "NGS/base/mpl/sequence/sequence.h"
#include "NGS/base/mpl/struct/var.h"


NGS_BEGIN
NGS_MPL_BEGIN


NGS_mfunction(_StructVar, CTemplate<member_var> _Var, CIntegralConstant _Index) {
	NGS_mcst size_t index = _Index::value;
	NGS_mcst_t var = _Var;

	NGS_mreturn_t var;
	NGS_mreturn index;
};

NGS_mfunction(meta_struct, class...);
NGS_mfunction(meta_struct, CTemplate<_StructVar>... _SVar) < _SVar... > {
private:
	NGS_mcst_t _sequence = boost::mpl::vector<_SVar...>;
	template<class _Var>
	NGS_mcst_t _var_t = typename _Var::type;
public:
	/** @brief 第n个元变量 */
	template<size_t _Index>
	NGS_mcst_t var_at = typename boost::mpl::at_c<_sequence, _Index>::type::type;
	/** @brief 第n个元变量的返回值 */
	template<size_t _Index>
	NGS_mcst_t var_at_t = typename var_at<_Index>::type;

	/** @brief 元变量个数 */
	NGS_mcst size_t count = sizeof...(_SVar);
	/** @brief 元结构体大小 */
	NGS_mcst size_t size = (0 + ... + _var_t<_SVar>::size);
private:
	NGS_mcst std::array<size_t, count> _sizes = { { _var_t<_SVar>::size... } };
	template<size_t _Index>
	NGS_mcst size_t _offset = _offset<_Index - 1> +_sizes[_Index - 1];
	template<>
	NGS_mcst size_t _offset<0> = 0;
public:
	/** @brief 元变量对应的动态结构体数组（可动态访问） */
	NGS_mcst std::array<member_var_d, count> vars = { member_var_d{_SVar::var::count, _SVar::var::size,_offset<_SVar::index>, }... };

	NGS_mreturn_t meta_struct<_SVar...>;

	byte data[size];
};

NGS_mfunction(member_var, CTemplate<meta_struct> _Struct, CIntegralConstant _Num) < _Struct, _Num > {
	static_assert(_Num::value == 1, "when member_var is used in meta_struct, the count must be 1");
	NGS_mcst_t element_type = _Struct;
	NGS_mcst size_t count = _Num::value;
	NGS_mcst size_t element_size = _Struct::size;
	NGS_mcst size_t size = count * element_size;

	NGS_mcst_t view = _Struct;
	NGS_mcst_t container = typename _Struct::type;
	NGS_mcst_t type = view;
};

NGS_mfunction(_make_meta_struct, class, class...);
NGS_mfunction(_make_meta_struct, CTemplate<member_var>... _Var, size_t... _Index) < std::index_sequence<_Index...>, _Var... > {
	NGS_mreturn_t meta_struct<_StructVar<_Var, std::integral_constant<size_t, _Index>>...>;
};

/**
 * @brief 元结构体
 *
 * @tparam var... 元变量
 *
 * @return 一个能够存储所有元变量的类型
 */
template<CTemplate<member_var>... _Var>
using meta_struct_c = typename _make_meta_struct<std::make_index_sequence<sizeof...(_Var)>, _Var...>::type;

template<CTemplate<member_var>... _Var>
using meta_struct_t = typename meta_struct_c<_Var...>::type;

struct meta_struct_d {
	size_t count;
	size_t size;
	std::span<const member_var_d> vars;
};

template<CTemplate<meta_struct> _Struct>
consteval meta_struct_d make_meta_struct() { return { _Struct::count, _Struct::size, _Struct::vars }; }


NGS_mfunction(push_front, class... _Element, class... _Args) < sequence<_Args...>, sequence<_Element...> > {
	NGS_mreturn_t sequence<_Element..., _Args...>;
};


NGS_END
NGS_CONCEPT

template<class T>
concept CMetaStruct = requires() {
	typename T::template var_at<0>;
	typename T::template var_at_t<0>;
	{T::count} -> std::convertible_to<size_t>;
	{T::size} -> std::convertible_to<size_t>;
	{T::vars} -> std::ranges::random_access_range;
	typename T::type;
};

NGS_END
NGS_END


