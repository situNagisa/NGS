#pragma once

#include "../param.h"
#include "./concept.h"
#include "./packer.h"
#include "./param_at.h"
#include "./size.h"
#include "./unpack.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _T>
concept is_storage_packer = is_packer<_T> && is_packer<typename type_traits::object_t<_T>::packer_type>;

template<class... _Args>
struct storage_packer : packer<type_traits::storage_t<_Args>...>
{
	NGS_MPL_ENVIRON2(storage_packer, packer<type_traits::storage_t<_Args>...>);
public:
	using packer_type = packer<_Args...>;

	constexpr storage_packer(auto&&... args)
		: base_type(type_traits::store<_Args>(NGS_PP_PERFECT_FORWARD(args))...)
	{}
	using base_type::operator=;
};

template<class... _Args>
storage_packer(_Args...) -> storage_packer<_Args...>;

template<size_t _Index>
constexpr decltype(auto) unpack(is_storage_packer auto&& param_packer)
{
	using packer_type = typename type_traits::object_t<decltype(param_packer)>::packer_type;
	return type_traits::restore<param_at_t<packer_type, _Index>>(NGS_PP_PERFECT_FORWARD(param_packer).template get<_Index>());
}

namespace _detail
{
	template<size_t... _Index>
	constexpr decltype(auto) apply(std::index_sequence<_Index...>, auto&& callable, is_storage_packer auto&& packer, auto&&... params)
	{
		return NGS_PP_PERFECT_FORWARD(callable)(
			NGS_FUNCTIONAL_PARAM_NS::forward_replace(
				NGS_LIB_MODULE_NAME::unpack<_Index>(NGS_PP_PERFECT_FORWARD(packer)),
				NGS_PP_PERFECT_FORWARD(params)...
			)...);
	}
}

constexpr decltype(auto) apply(auto&& callable, is_storage_packer auto&& packer, auto&&... params)
{
	return _detail::apply(
		::std::make_index_sequence<packer_size<decltype(packer)>>(),
		NGS_PP_PERFECT_FORWARD(callable),
		NGS_PP_PERFECT_FORWARD(packer), NGS_PP_PERFECT_FORWARD(params)...);
}

NGS_LIB_MODULE_END
NGS_LIB_MODULE_EXPORT(is_storage_packer);
NGS_LIB_MODULE_EXPORT(storage_packer);
NGS_LIB_MODULE_EXPORT(unpack);
NGS_LIB_MODULE_EXPORT(apply);
