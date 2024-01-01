#pragma once

#include "./concept.h"
#include "../packer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _FunctionType, class... _Params>
struct binder
{
protected:
	using self_type = binder;
public:
	using type_category = _detail::binder_tag;
	using function_type = _FunctionType;
	using packer_type = NGS_FUNCTIONAL_PACKER_NS::storage_packer<_Params...>;
private:
	using function_storage_type = std::decay_t<function_type>;
	using packer_storage_type = packer_type;// parameter_pack<std::decay_t<_Args>...>;
public:
	constexpr explicit binder(auto&& function, auto&&... params)// requires requires{ function_storage_type(NGS_PP_PERFECT_FORWARD(function)); args_storage_type(NGS_PP_PERFECT_FORWARD(args)...); }
		: _function(NGS_PP_PERFECT_FORWARD(function))
		, _packer(NGS_PP_PERFECT_FORWARD(params)...)
	{}

public:
	constexpr static decltype(auto) _call(auto&& self, auto&&... params)
	{
		return NGS_FUNCTIONAL_PACKER_NS::apply(self._function, self._packer, NGS_PP_PERFECT_FORWARD(params)...);
	}
public:
	constexpr decltype(auto) operator()(auto&&... params)
	{
		return self_type::_call(*this, NGS_PP_PERFECT_FORWARD(params)...);
	}
	constexpr decltype(auto) operator()(auto&&... params) const
	{
		return self_type::_call(*this, NGS_PP_PERFECT_FORWARD(params)...);
	}

	//for `structured type`
public:
	function_storage_type _function;
	packer_storage_type _packer;
};

#if defined(__cpp_deduction_guides)
template<class _FunctionType, class... _Args>
binder(_FunctionType&&, _Args&&...) -> binder<_FunctionType, _Args...>;
#endif

[[nodiscard]] constexpr decltype(auto) bind(auto&& function, auto&&... args)
{
	return binder<decltype(function), decltype(args)...>(NGS_PP_PERFECT_FORWARD(function), NGS_PP_PERFECT_FORWARD(args)...);
}

namespace _detail
{
	template<size_t _Offset, size_t... _Index>
	constexpr decltype(auto) bind_on_sequence(::std::index_sequence<_Index...>, auto&& functor, auto&&... args)
	{
		return NGS_LIB_MODULE_NAME::bind(NGS_PP_PERFECT_FORWARD(functor), NGS_PP_PERFECT_FORWARD(args)..., placeholders::n<_Index + _Offset + 1>...);
	}
}

template<size_t _Sequence, size_t _Offset = 0>
constexpr decltype(auto) bind(auto&& functor, auto&&... args)
{
	return _detail::bind_on_sequence<_Offset>(::std::make_index_sequence<_Sequence>(), NGS_PP_PERFECT_FORWARD(functor), NGS_PP_PERFECT_FORWARD(args)...);
}

NGS_LIB_MODULE_END
NGS_LIB_MODULE_EXPORT(binder);
NGS_LIB_MODULE_EXPORT(bind);