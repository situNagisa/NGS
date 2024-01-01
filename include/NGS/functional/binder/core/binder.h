#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace _detail
{
	struct binder_tag {};
}


template<class _FunctionType, parameter_packet::packet_like _Pack>
struct binder
{
protected:
	using self_type = binder;
public:
	using type_category = _detail::binder_tag;
	using function_type = _FunctionType;
	using packet_type = type_traits::naked_t<_Pack>;
private:
	using function_storage_type = std::decay_t<function_type>;
public:
	constexpr explicit binder(auto&& function, const packet_type& packet)
		: _function(NGS_PP_PERFECT_FORWARD(function))
		, _packet(NGS_PP_PERFECT_FORWARD(packet))
	{}

public:
	constexpr static decltype(auto) _call(auto&& self, auto&&... params)
	{
		return parameter_packet::apply(self._function, self._packet, NGS_PP_PERFECT_FORWARD(params)...);
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
	std::decay_t<function_type> _function;
	packet_type _packet;
};

template<class _T>
concept is_binder = std::derived_from<typename type_traits::object_t<_T>::type_category, _detail::binder_tag>;

NGS_LIB_MODULE_END