#pragma once

#if __has_include(<boost/config.hpp>)
#	include <boost/config.hpp>
#	include <boost/version.hpp>
#	define NGS_CONFIG_LIB_BOOST BOOST_VERSION
#else
//#	define NGS_CONFIG_LIB_BOOST 0
#endif

