#pragma once

#include "../defined.h"

#include "NGS/external/boost/mpl.h"

#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/iterator.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/support.hpp>

#define NGS_BOOST_FUSION_BEGIN NGS_BOOST_BEGIN namespace fusion {
#define NGS_BOOST_FUSION_END } NGS_BOOST_END

#define NGS_BOOST_FUSION_RESULT_OF_BEGIN NGS_BOOST_FUSION_BEGIN namespace result_of {
#define NGS_BOOST_FUSION_RESULT_OF_END } NGS_BOOST_FUSION_END
