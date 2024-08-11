#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class HandleType, HandleType Null = {}>
	requires ::std::constructible_from<HandleType> && ::std::equality_comparable<HandleType> && ::std::movable<HandleType> && ::std::assignable_from<HandleType&, HandleType>
struct basic_handle : bases::delete_copy
{
	NGS_PP_INJECT_BEGIN(basic_handle);
public:
	using handle_type = HandleType;
	constexpr static handle_type null = Null;

	constexpr explicit(false) basic_handle(const handle_type& handle = null) noexcept : _handle(handle) {}
	constexpr basic_handle(self_type&& other)noexcept : _handle(::std::move(other._handle))
	{
		other._handle = null;
	}
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
	constexpr ~basic_handle()
	{
		_handle = null;
	}
#endif
	constexpr self_type& operator=(self_type&& other) noexcept
	{
		if (!::std::is_constant_evaluated())
			NGS_EXPECT(_handle == null);
		_handle = ::std::move(other._handle);
		other._handle = null;
		return *this;
	}

	constexpr void clear_handle() noexcept { _handle = null; }

	constexpr auto&& get_handle() const noexcept { return _handle; }
private:
	handle_type _handle{};
};

NGS_LIB_END