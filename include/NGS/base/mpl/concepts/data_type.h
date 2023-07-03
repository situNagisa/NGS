#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/boost/mpl.h"
#include "NGS/base/mpl/concepts/meta_function.h"

NGS_BEGIN
NGS_CONCEPT

template<class N>
concept CMetaIntegralConstant = CMetaFunction<N> && requires() {
	{N::value} -> std::convertible_to<typename N::value_type>;
		requires std::same_as<N, typename N::type>;
	typename boost::mpl::next<N>::type;
	typename boost::mpl::prior<N>::type;
		requires std::same_as<boost::mpl::integral_c_tag, typename N::tag>;
};
//static_assert(CMetaIntegralConstant< boost::mpl::size<boost::mpl::vector<>>::type>);

NGS_END
NGS_END
