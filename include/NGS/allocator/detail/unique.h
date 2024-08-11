#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

inline constexpr auto default_deleter = [](auto&& handle)
	{};

template<resources::resource Handle, ::std::copy_constructible Deleter = decltype(default_deleter)>
	requires ::std::invocable<Deleter, Handle>
struct unique_resource : bases::delete_copy
{
	NGS_PP_INJECT_BEGIN(unique_resource);
public:
	using handle_type = Handle;
	using deleter_type = Deleter;

	constexpr explicit(false) unique_resource(const deleter_type& deleter, auto&&... handle_args) requires ::std::constructible_from<handle_type, decltype(handle_args)...>
		: _deleter(deleter)
		, _handle(NGS_PP_PERFECT_FORWARD(handle_args)...)
	{
	}
	constexpr explicit(false) unique_resource(auto&&... handle_args) requires ::std::default_initializable<deleter_type> && ::std::constructible_from<handle_type, decltype(handle_args)...>
		: self_type(deleter_type{}, NGS_PP_PERFECT_FORWARD(handle_args)...)
	{
	}

	constexpr unique_resource(self_type&& other) noexcept
		: _deleter(::std::move(other._deleter))
		, _handle(::std::move(other._handle))
	{
		other._holder = false;
	}
	constexpr ~unique_resource() noexcept
	{
		release();
	}

	constexpr auto release() noexcept
	{
		if (!_holder)
			return;
		_deleter(::std::move(_handle));
		_holder = false;
	}

	constexpr self_type& operator=(self_type&& other) noexcept
	{
		if (this == &other)
			return *this;
		release();
		_deleter = ::std::move(other._deleter);
		_handle = ::std::move(other._handle);
		other.release();
		return *this;
	}

	[[nodiscard]] constexpr auto&& value() const noexcept
	{
		return _handle;
	}
	[[nodiscard]] constexpr bool valid() const noexcept
	{
		return _holder;
	}

	deleter_type _deleter{};
	handle_type _handle;
	bool _holder = true;
};

template<resources::resource Handle>
struct unique_allocator
{
	NGS_PP_INJECT_BEGIN(unique_allocator);
public:
	struct deleter
	{
		constexpr deleter(self_type& allocator) : _allocator(::std::addressof(allocator)) {}

		constexpr void operator()(Handle&& handle) const noexcept
		{
			_allocator->deallocate(::std::move(handle));
		}

		unique_allocator* _allocator;
	};
	using value_type = unique_resource<Handle, deleter>;

	constexpr unique_allocator() = default;
	constexpr explicit(false) unique_allocator(::std::ranges::input_range auto&& range) requires ::std::constructible_from<Handle, ::std::ranges::range_value_t<decltype(range)>>
	{
		for (auto&& item : NGS_PP_PERFECT_FORWARD(range))
		{
			_resources.emplace_front(deleter(*this), NGS_PP_PERFECT_FORWARD(item));
		}
	}

	constexpr auto allocate()
	{
		auto front = ::std::move(_resources.front());
		_resources.pop_front();
		return front;
	}

	constexpr void deallocate(value_type&& value)
	{
		_resources.emplace_front(::std::move(value));
	}
	constexpr void deallocate(Handle&& handle)
	{
		_resources.emplace_front(deleter(*this), ::std::move(handle));
	}

	::std::forward_list<value_type> _resources{};
};


NGS_LIB_MODULE_END