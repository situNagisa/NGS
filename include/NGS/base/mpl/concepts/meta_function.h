#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/boost/mpl.h"

NGS_BEGIN
NGS_CONCEPT

template<class F>
concept CMetaFunction = requires() {
	typename F::type;
};

template<class F, class... _Args>
concept CMetaFunctionClass = ((sizeof...(_Args) == 0) && requires() {
	typename F::apply::type;
} || requires() {
	typename F::template apply<>::type;
}) || requires() {
	typename F::template apply<_Args...>::type;
};

template<class F>
concept CMetaPlaceholder = requires() {
	requires std::same_as<boost::mpl::arg<F::value>, F>;
};

template<class F, class... _Args>
concept CMetaPlaceholderExpression = CMetaPlaceholder<F> || requires() {
	requires (!sizeof...(_Args)) || (CMetaPlaceholder<_Args> || ...);
	requires sizeof...(_Args) < BOOST_MPL_LIMIT_METAFUNCTION_ARITY;
};

static_assert(CMetaPlaceholderExpression<boost::mpl::_1>);
//static_assert(CMetaPlaceholderExpression<boost::mpl::plus< boost::mpl::_, boost::mpl::int_<2>>>);
//static_assert(CMetaPlaceholderExpression < boost::mpl::if_< boost::mpl::less< boost::mpl::_1, boost::mpl::int_<7>>, boost::mpl::plus< boost::mpl::_1, boost::mpl::_2>, boost::mpl::_1>>);

template<class F, class... _Args>
concept CMetaLambda = CMetaFunctionClass<F, _Args...>;


NGS_END
NGS_END
