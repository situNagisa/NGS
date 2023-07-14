#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/mpl/mpl_macro.h"
#include "NGS/base/mpl/concepts/concept.h"
#include "NGS/base/mpl/sequence.h"

NGS_BEGIN
NGS_MPL_BEGIN

NGS_mfunction(member_var, class _Type, CIntegralConstant _Num) {
	NGS_mcst_t element_type = _Type;
	NGS_mcst size_t count = _Num::value;
	NGS_mcst size_t element_size = sizeof(element_type);
	NGS_mcst size_t size = count * element_size;

	NGS_mcst_t view = std::span<element_type, count>;
	NGS_mcst_t container = std::array<element_type, count>;
	NGS_mcst_t type = view;
};

struct member_var_d {
	size_t count;
	size_t size;
	size_t offset;
};

template<class _Type, size_t _Count = 1>
using member_var_c = member_var<_Type, std::integral_constant<size_t, _Count>>;
template<class _Type, size_t _Count = 1>
using var_ = member_var_c<_Type, _Count>;


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
	template<size_t _Index>
	NGS_mcst_t var_at = typename boost::mpl::at_c<_sequence, _Index>::type::type;
	template<size_t _Index>
	NGS_mcst_t var_at_t = typename var_at<_Index>::type;

	NGS_mcst size_t count = sizeof...(_SVar);
	NGS_mcst size_t size = (0 + ... + _var_t<_SVar>::size);
private:
	NGS_mcst std::array<size_t, count> _sizes = { { _var_t<_SVar>::size... } };
	template<size_t _Index>
	NGS_mcst size_t _offset = _offset<_Index - 1> +_sizes[_Index - 1];
	template<>
	NGS_mcst size_t _offset<0> = 0;
public:
	NGS_mcst std::array<member_var_d, count> vars = { member_var_d{_SVar::var::count, _SVar::var::size,_offset<_SVar::index>, }... };

	NGS_mreturn_t std::array<byte, size>;
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

NGS_mfunction(_StructVarToMemberVar, class);
NGS_mfunction(_StructVarToMemberVar, CTemplate<member_var> _Var, size_t _Index) < _StructVar<_Var, std::integral_constant<size_t, _Index>> > {
	NGS_mreturn_t _Var;
};

NGS_mfunction(_MetaStructToSequence, class);
NGS_mfunction(_MetaStructToSequence, class... _StructVars) < meta_struct<_StructVars...> > {
	NGS_mreturn_t sequence<typename _StructVarToMemberVar<_StructVars>::type ...>;
};

NGS_mfunction(_MetaStructSpread, class);
NGS_mfunction(_MetaStructSpread, CTemplate<member_var> _Var) < sequence<_Var> > {
	NGS_mreturn_t sequence<_Var>;
};
NGS_mfunction(_MetaStructSpread, CTemplate<meta_struct> _Struct, size_t _Count) < sequence<member_var<_Struct, std::integral_constant<size_t, _Count>>> > {
	NGS_mreturn_t typename _MetaStructToSequence<_Struct>::type;
};
NGS_mfunction(_MetaStructSpread, CTemplate<member_var> _Var, CTemplate<member_var>... _Vars)
< sequence<_Var, _Vars...> > {
	NGS_mreturn_t typename push_front<typename _MetaStructSpread<sequence<_Vars...>>::type, _Var>::type;
};
NGS_mfunction(_MetaStructSpread, CTemplate<meta_struct> _Struct, size_t _Count, CTemplate<member_var>... _Vars)
< sequence<member_var<_Struct, std::integral_constant<size_t, _Count>>, _Vars...> > {
	NGS_mreturn_t typename push_front<typename _MetaStructSpread<sequence<_Vars...>>::type, typename _MetaStructSpread<typename _MetaStructToSequence<_Struct>::type>::type>::type;
};

NGS_mfunction(spread_struct, CTemplate<meta_struct> _Struct, class = typename _MetaStructSpread<typename _MetaStructToSequence<_Struct>::type>::type);
NGS_mfunction(spread_struct, CTemplate<meta_struct> _Struct, CTemplate<member_var>... _Var) < _Struct, sequence<_Var...> > {
	NGS_mreturn_t meta_struct_c<_Var...>;
};
template<CTemplate<meta_struct> _Struct>
using spread_struct_t = typename spread_struct<_Struct>::type;

NGS_END
NGS_END
