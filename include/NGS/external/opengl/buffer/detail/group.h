#pragma once

#include "./context.h"
#include "./defined.h"


NGS_LIB_MODULE_BEGIN

template<buffer_context... Context>
struct group : ::std::ranges::view_interface<group<Context...>>
{
	NGS_PP_INJECT_EXPLICIT(group, ::std::ranges::view_interface<group<Context...>>);
public:
	using group_type = ::std::tuple<Context...>;

	explicit(false) group(auto&& context_group) requires ::std::constructible_from<group_type, decltype(context_group)>
		: _group(NGS_PP_PERFECT_FORWARD(context_group))
	{}
	template<class... Args>
		requires ((::std::constructible_from<Context, Args&&...>) && ...)
	explicit(sizeof...(Args) == 0) group(Args&&... context_constructor_args)
		: self_type(::std::make_tuple(Context{ NGS_PP_PERFECT_FORWARD(context_constructor_args)... }...))
	{}

	group(size_t size, enums::usage usage, auto&&... context_constructor_args) requires ((::std::constructible_from<Context, decltype(context_constructor_args)...>) && ...)
		: self_type(NGS_PP_PERFECT_FORWARD(context_constructor_args)...)
	{
		allocate(size, usage);
	}
	group(enums::usage usage, /* tuple like */ const auto& data_tuple, auto&&... context_constructor_args) requires ((::std::constructible_from<Context, decltype(context_constructor_args)...>) && ...)
		: self_type(NGS_PP_PERFECT_FORWARD(context_constructor_args)...)
	{
		self_type::describe(usage, data_tuple);
	}

	void allocate(size_t size, enums::usage usage) const
	{
		stl::tuples::for_each(_group, [&](auto&& context)
			{
				contextes::bind(NGS_PP_PERFECT_FORWARD(context));
				NGS_PP_PERFECT_FORWARD(context).allocate(size, usage);
			});
	}

	void describe(enums::usage usage, /* tuple like */ const auto& data_tuple) const
		requires (::std::tuple_size_v<::std::remove_reference_t<decltype(data_tuple)>> == sizeof...(Context))
	{
		[&] <::std::size_t... Index>(::std::index_sequence<Index...>)
		{
			((
				(contextes::bind(NGS_PP_PERFECT_FORWARD(context_at<Index>())))
				, (NGS_PP_PERFECT_FORWARD(context_at<Index>()).describe(::std::get<Index>(data_tuple), usage))
				), ...);
		}(::std::make_index_sequence<sizeof...(Context)>{});
	}

	decltype(auto) submit(/* tuple like */ const auto& data_tuple) const
	{
		return self_type::submit(0, data_tuple);
	}
	void submit(size_t offset, /* tuple like */ const auto& data_tuple) const
		requires (::std::tuple_size_v<::std::remove_reference_t<decltype(data_tuple)>> == sizeof...(Context))
	{
		[&] <::std::size_t... Index>(::std::index_sequence<Index...>)
		{
			((
				(contextes::bind(NGS_PP_PERFECT_FORWARD(context_at<Index>())))
				, (NGS_PP_PERFECT_FORWARD(context_at<Index>()).describe(::std::get<Index>(data_tuple), offset))
				), ...);
		}(::std::make_index_sequence<sizeof...(Context)>{});
	}

	auto&& get_group(this auto&& self) { return self._group; }

	template<::std::size_t Index>
		requires (Index < sizeof...(Context))
	auto&& context_at(this auto&& self) { return ::std::get<Index>(self._group); }

	group_type _group;
};

NGS_LIB_MODULE_END