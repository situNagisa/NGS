#pragma once

#include "./defined.h"

NGS_MATH_LA_VECTOR_VIEW_BEGIN

template<
	auto _Accessor,
	ccpt::uint _Dimension,
	concepts::vectors::expression _Left,
	concepts::vectors::expression _Right,
	statics::functional::is_param... _Params
>
	requires std::invocable<decltype(_Accessor), _Left, _Right, traits::vectors::index_t, _Params...>
struct binary : containers::vectors::vector_expression<binary<_Accessor, _Dimension, _Left, _Right, _Params...>>
{
	NGS_MPL_ENVIRON(binary);
public:
	constexpr static size_t dimension = _Dimension::value;
	constexpr static size_t complexity = yap::complexity<_Left> +yap::complexity<_Right> +1;

	using left_closure_type = traits::vectors::closure_t<_Left>;
	using left_closure_param_type = traits::vectors::closure_param_t<_Left>;
	using right_closure_type = traits::vectors::closure_t<_Right>;
	using right_closure_param_type = traits::vectors::closure_param_t<_Right>;

	//using accessor_type = _AccessorType;
	constexpr static auto accessor = _Accessor;
	using packer_type = statics::functional::packer<left_closure_type, right_closure_type, statics::functional::placeholder<1>, _Params...>;

	constexpr binary(
		left_closure_param_type left, right_closure_param_type right,
		auto&&... params
	) requires (std::convertible_to<decltype(params), _Params> && ...)
		: packer(left, right, statics::functional::placeholders::_1, NGS_PP_PERFECT_FORWARD(params)...)
	{}

	constexpr decltype(auto) access(traits::vectors::index_t index)
	{
		return statics::functional::apply(accessor, packer, index);
	}
	constexpr decltype(auto) access(traits::vectors::index_t index) const
	{
		return statics::functional::apply(accessor, packer, index);
	}

	packer_type packer;
};



NGS_MATH_LA_VECTOR_VIEW_END