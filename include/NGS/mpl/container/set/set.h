#pragma once

#include "NGS/mpl/defined.h"
#include "NGS/mpl/container/vector/vector.h"
#include "NGS/mpl/container/vector/algorithm/unique.h"
#include "NGS/mpl/utils/is_same_with_any_of.h"
#include "NGS/mpl/functor/equal.h"
#include "NGS/mpl/utils/template.h"

NGS_MPL_BEGIN

template<class _Associative>
concept CSet = requires(_Associative sequence, const _Associative sequence_cst) {
	requires ccpt::Predicate<typename _Associative::template equal_functor<void, void>>;
	
	{ _Associative::size } -> std::convertible_to<size_t>;
	{ _Associative::template contain<void> } -> std::convertible_to<bool>;
	typename _Associative::template insert<void>;
};

NGS_mfunction(set, template<class...>class _Equal = equal, class... _Element);

NGS_mfunction(set, template<class, class>class _Equal, class... _Element) < _Equal, _Element... > {
public:
	using self_type = set;

	using container = unique_t<vector<_Element...>,_Equal>;
public:
	template<class _Left, class _Right> NGS_mcst_t equal_functor = _Equal<_Left,_Right>;
	template<class _Left, class _Right> NGS_mcst_t equal_functor_t = typename _Equal<_Left, _Right>::result_type;
	template<class _Left, class _Right> NGS_mcst bool equal_functor_v = equal_functor_t<_Left, _Right>::value;

	NGS_mcst size_t size = container::size;

	template<class _Type> constexpr static bool contain = is_same_with_any_of<container, _Type,equal_functor>::result_type::value;

	template<class _NewElement> NGS_mcst_t insert = std::conditional_t<
		contain<_NewElement>, 
		self_type, 
		set<equal_functor, _Element..., _NewElement>
	>;

	template<ccpt::UInt _Index> using element_at = typename container::template at<_Index>;
	template<size_t _Index> using element_at_c = element_at<ccpt::uint_<_Index>>;
};
template<class... _Elements>
using set_ = set<equal, _Elements...>;

NGS_CCPT_VERIFY(CSet, set_<int, float>);

NGS_MPL_END
