#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class _Info, class... _Args>
struct vulkan_object
{
	NGS_MPL_ENVIRON_BEGIN(vulkan_object);
public:
	using info_type = _Info;

	vulkan_object(auto&& info, auto&&... args)
		: _info(NGS_PP_PERFECT_FORWARD(info))
		, _args(NGS_PP_PERFECT_FORWARD(args)...)
	{
	}

	auto&& get_info() { return _info; }

	info_type _info;
	::std::tuple<_Args...> _args;
};

NGS_LIB_END
