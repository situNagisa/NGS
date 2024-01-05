#include "./defined.h"

#if !defined(NGS_MATH_VECTOR_ARITHMETIC_ID)
#	error "NGS_MATH_VECTOR_ARITHMETIC_ID must be defined"
#endif

#if !defined(NGS_MATH_VECTOR_ARITHMETIC_CONCEPT_ID)
#	error "NGS_MATH_VECTOR_ARITHMETIC_CONCEPT_ID must be defined"
#endif

#if !defined(NGS_MATH_VECTOR_ARITHMETIC_OP)
#	error "NGS_MATH_VECTOR_ARITHMETIC_OP must be defined"
#endif

NGS_MATH_LA_VECTOR_CONCEPT_BEGIN

template<class _Left, class _Right>
concept NGS_MATH_VECTOR_ARITHMETIC_CONCEPT_ID = arithmetic_operatable_with<_Left, _Right>&& cpt::NGS_MATH_VECTOR_ARITHMETIC_CONCEPT_ID<traits::vectors::value_t<_Left>, traits::vectors::value_t<_Right>>;

NGS_MATH_LA_VECTOR_CONCEPT_END
NGS_MATH_LA_VECTOR_VIEW_BEGIN

inline constexpr struct
{
	template<class _Left, class _Right>
		requires concepts::vectors::NGS_MATH_VECTOR_ARITHMETIC_CONCEPT_ID <_Left, _Right>
	struct view
		: containers::vectors::vector_expression<view<_Left, _Right>>
	{
		constexpr static traits::vectors::dimension_t dimension = adapters::vectors::static_dimension<_Left>;
		constexpr static size_t complexity = yap::complexity<_Left> +yap::complexity<_Right> +1;

		using left_closure_type = traits::vectors::closure_t<_Left>;
		using left_closure_param_type = traits::vectors::closure_param_t<_Left>;
		using right_closure_type = traits::vectors::closure_t<_Right>;
		using right_closure_param_type = traits::vectors::closure_param_t<_Right>;

		constexpr view(left_closure_param_type left, right_closure_param_type right)
			: left(left)
			, right(right)
		{}

		constexpr decltype(auto) access(traits::vectors::index_t index)
		{
			return adapters::vectors::access(left, index) NGS_MATH_VECTOR_ARITHMETIC_OP adapters::vectors::access(right, index);
		}
		constexpr decltype(auto) access(traits::vectors::index_t index) const
		{
			return adapters::vectors::access(left, index) NGS_MATH_VECTOR_ARITHMETIC_OP adapters::vectors::access(right, index);
		}

		left_closure_type left;
		right_closure_type right;
	};

	constexpr decltype(auto) operator()(concepts::vectors::expression auto&& left, concepts::vectors::expression auto&& right)const
		//requires concepts::vectors::NGS_MATH_VECTOR_ARITHMETIC_CONCEPT_ID<decltype(left), decltype(right)>
	{
		return view<decltype(left), decltype(right)>(
			NGS_PP_PERFECT_FORWARD(left),
			NGS_PP_PERFECT_FORWARD(right)
		);
	}

}NGS_MATH_VECTOR_ARITHMETIC_ID{};

constexpr decltype(auto) operator NGS_MATH_VECTOR_ARITHMETIC_OP(concepts::vectors::expression auto&& left, concepts::vectors::expression auto&& right)
	requires concepts::vectors::NGS_MATH_VECTOR_ARITHMETIC_CONCEPT_ID<decltype(left), decltype(right)>
{
	return NGS_MATH_VECTOR_ARITHMETIC_ID(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_MATH_LA_VECTOR_VIEW_END

#undef NGS_MATH_VECTOR_ARITHMETIC_ID
#undef NGS_MATH_VECTOR_ARITHMETIC_CONCEPT_ID
#undef NGS_MATH_VECTOR_ARITHMETIC_OP