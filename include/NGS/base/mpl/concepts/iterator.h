#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/boost/mpl.h"
#include "NGS/base/mpl/concepts/data_type.h"

NGS_BEGIN
NGS_CONCEPT

template<class I>
concept CMetaIterator = requires() {
	typename boost::mpl::deref<I>::type;
};

template<class I>
concept CMetaForwardIterator = CMetaIterator<I> && requires() {
	typename boost::mpl::next<I>::type;
	//requires CForwardIterator<typename boost::mpl::next<I>::type>;
	//requires std::convertible_to<typename I::category, boost::mpl::forward_iterator_tag>;
};

template<class I>
concept CMetaBidirectionalIterator = CMetaForwardIterator<I> && requires() {
	typename boost::mpl::prior<I>::type;
	//requires CBidirectionalIterator<typename boost::mpl::prior<I>::type>;
	//requires std::convertible_to<typename I::category, boost::mpl::bidirectional_iterator_tag>;
};

template<class I>
concept CMetaRandomAccessIterator = CMetaBidirectionalIterator<I> && requires() {
	typename boost::mpl::advance<I, boost::mpl::int_<0>>::type;
	typename boost::mpl::distance<I, I>::type;
	//requires CRandomAccessIterator<typename boost::mpl::advance<I, int>::type>;
	//requires std::convertible_to<typename I::category, boost::mpl::random_access_iterator_tag>;
};
//tatic_assert(CMetaRandomAccessIterator<boost::mpl::begin<boost::mpl::list<int, int>>>);


NGS_END
NGS_END
