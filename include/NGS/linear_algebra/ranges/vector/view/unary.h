#pragma once

#include "./defined.h"

NGS_MATH_LA_VECTOR_VIEW_BEGIN

template<
	auto _Access,
	concepts::vectors::expression _Vector,
	size_t _Dimension,
	statics::functional::is_param... _Params
>
	requires std::invocable<decltype(_Access), traits::vectors::closure_t<_Vector>, traits::vectors::index_t, _Params...>
struct unary : yap::expression<unary<_Access, _Vector, _Dimension, _Params...>>
{
	constexpr static size_t dimension = _Dimension;
	constexpr static size_t complexity = yap::complexity<_Vector> +1;
	constexpr static auto accessor = _Access;

	using closure_type = traits::vectors::closure_t<_Vector>;
	using closure_param_type = traits::vectors::closure_param_t<_Vector>;
	using packer_type = statics::functional::packer<closure_type, statics::functional::placeholder<1>, _Params...>;

	constexpr unary(closure_param_type vector, auto&&... params) requires (std::convertible_to<decltype(params), _Params> && ...)
		: packer(vector, statics::functional::placeholders::_1, NGS_PP_PERFECT_FORWARD(params)...)
	{}

	constexpr decltype(auto) access(traits::vectors::index_t index)
	{
		return statics::functional::apply(accessor, packer);
	}
	constexpr decltype(auto) access(traits::vectors::index_t index) const
	{
		return statics::functional::apply(accessor, packer);
	}

	packer_type packer;
};

NGS_MATH_LA_VECTOR_VIEW_END