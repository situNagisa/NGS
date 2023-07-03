#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/boost/mpl.h"
#include "NGS/base/mpl/concepts/iterator.h"

NGS_BEGIN
NGS_CONCEPT

template <class S>
concept CMetaFowardSequence = requires() {
	typename boost::mpl::front<S>::type;
		requires CMetaForwardIterator<typename boost::mpl::begin<S>::type>;
		requires CMetaForwardIterator<typename boost::mpl::end<S>::type>;
		requires CMetaIntegralConstant<typename boost::mpl::size<S>::type>;
		requires CMetaIntegralConstant<typename boost::mpl::empty<S>::type>;
};

template<class S>
concept CMetaBidirectionalSequence = CMetaFowardSequence<S> && requires() {
	typename boost::mpl::back<S>::type;
		requires CMetaBidirectionalIterator<typename boost::mpl::begin<S>::type>;
		requires CMetaBidirectionalIterator<typename boost::mpl::end<S>::type>;
};

template<class S>
concept CMetaRandomAccessSequence = CMetaBidirectionalSequence<S> && requires() {
	typename boost::mpl::at<S, boost::mpl::int_<0>>::type;
		requires CMetaRandomAccessIterator<typename boost::mpl::begin<S>::type>;
		requires CMetaRandomAccessIterator<typename boost::mpl::end<S>::type>;
};
//static_assert(CMetaRandomAccessSequence<boost::mpl::vector<int, int, int>>);

NGS_END
NGS_END
