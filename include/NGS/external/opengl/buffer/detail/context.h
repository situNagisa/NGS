#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

NGS_TCEA_TRAIT_DEFAULT(context_target);
NGS_TCEA_TRAIT_ALIAS_V(context_target);
NGS_TCEA_TRAIT_HAS_VALUE(context_target, target);
NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(allocate, (::std::convertible_to<::std::size_t>, ::std::convertible_to<enums::usage>));
NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(describe, (::std::ranges::contiguous_range, ::std::convertible_to<enums::usage>));
NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(submit, (::std::ranges::contiguous_range, ::std::convertible_to<::std::size_t>));

namespace _detail
{
	auto buffer_creator()
	{
		contextes::context_t context;
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glGenBuffers(1, &context));
		return context;
	}
	void buffer_deleter(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glDeleteBuffers(1, &context));
	}
	template<enums::buffer_target Target>
	void buffer_binder(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glBindBuffer(::std::to_underlying(Target), context));
	}

	NGS_EXTERNAL_OPENGL_CONTEXT_DEFINE_BASIC_CONTEXT(unknown_buffer, _detail::buffer_creator, _detail::buffer_deleter);
}

template<class T, class DataRange = ::std::span<::std::byte>>
concept buffer_context = ::std::derived_from<::std::remove_reference_t<T>, _detail::unknown_buffer> && requires(T target, DataRange data, ::std::size_t size, enums::usage usage)
{
	{ context_target_v<::std::remove_reference_t<T>> } -> ::std::convertible_to<enums::buffer_target>;
	{ allocate(NGS_PP_PERFECT_FORWARD(target), size, usage) };
	{ describe(NGS_PP_PERFECT_FORWARD(target), NGS_PP_PERFECT_FORWARD(data), usage) };
	{ submit(NGS_PP_PERFECT_FORWARD(target), NGS_PP_PERFECT_FORWARD(data), size) };
};

template<enums::buffer_target Target>
struct context : _detail::unknown_buffer
{
	NGS_PP_INJECT(context);
public:
	constexpr static auto target = Target;

	using machine_type = contextes::context_machine<self_type, _detail::buffer_binder<target>>;

	using base_type::base_type;
	using base_type::operator=;
	context(self_type&&) = default;
	self_type& operator=(self_type&&) = default;
	~context()
	{
#if defined(NGS_EXTERNAL_OPENGL_CONTEXT_CHECK_BIND)
		if (contextes::is_binding(*this))
			contextes::unbind(*this);
#endif
	}

	void allocate(size_t size, enums::usage usage) const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glBufferData(::std::to_underlying(target), size, nullptr, ::std::to_underlying(usage)));
	}

	void describe(const ::std::ranges::contiguous_range auto& data, enums::usage usage) const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		constexpr auto value_size = sizeof(::std::ranges::range_value_t<decltype(data)>);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glBufferData(::std::to_underlying(target), ::std::ranges::size(data) * value_size, ::std::ranges::data(data), ::std::to_underlying(usage)));
	}

	void submit(const ::std::ranges::contiguous_range auto& data, size_t offset = 0) const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		constexpr auto value_size = sizeof(::std::ranges::range_value_t<decltype(data)>);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glBufferSubData(::std::to_underlying(target), offset * value_size, ::std::ranges::size(data) * value_size, ::std::ranges::data(data)));
	}
};


NGS_LIB_MODULE_END