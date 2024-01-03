#pragma once

#include "./binder.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) replace(is_binder auto&& binder, auto&&... args)
{
	return NGS_PP_PERFECT_FORWARD(binder)(NGS_PP_PERFECT_FORWARD(args)...);
}

NGS_LIB_MODULE_END

template<NGS_NS::NGS_LIB_NAME::NGS_LIB_MODULE_NAME::is_binder _Binder, class... _Args>
struct NGS_NS::functional::parameter_packet::meta_replace<_Binder, _Args...>
{
	using type = ::std::invoke_result_t<_Binder, _Args...>;
};