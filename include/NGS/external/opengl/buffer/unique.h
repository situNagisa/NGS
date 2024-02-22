#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _Value>
struct unique_buffer : bases::delete_copy
{
	NGS_MPL_ENVIRON_BEGIN(unique_buffer);
public:
	using value_type = _Value;

	constexpr unique_buffer() noexcept = default;
	constexpr unique_buffer(size_t count) noexcept requires ::std::constructible_from<value_type>
		: _count(count)
		, _value(::std::make_unique<value_type[]>(new value_type[_count]{}))
	{}
	constexpr unique_buffer(auto&&... values) requires (::std::constructible_from<value_type, decltype(values)> && ...)
		: _count(sizeof...(values))
		, _value(::std::make_unique<value_type[]>(new value_type[_count]{ NGS_PP_PERFECT_FORWARD(values)... }))
	{}
	constexpr unique_buffer(unique_buffer&& other) noexcept
		: _count(other._count)
		, _value(::std::move(other._value))
	{
		other._value.release();
		other._count = 0;
	}
	constexpr self_type& operator=(unique_buffer&& other) noexcept
	{
		_count = other._count;
		_value = ::std::move(other._value);
		other._value.release();
		other._count = 0;
		return *this;
	}

	void resize(size_t size)
	{
		auto new_value = ::std::make_unique<value_type[]>(new value_type[size]{});

		if constexpr (::std::is_trivially_copy_constructible_v<value_type>)
		{
			::std::memcpy(new_value.get(), _value.get(), ::std::min(_count, size) * sizeof(value_type));
		}
		else
		{
			for (size_t i = 0; i < ::std::min(_count, size); ++i)
			{
				new_value[i] = ::std::move(_value[i]);
			}
		}
		_value = ::std::move(new_value);
		_count = size;
	}



	constexpr auto size() const noexcept { return _count; }
	constexpr auto data() noexcept { return _value.get(); }
	constexpr auto data() const noexcept { return _value.get(); }

	constexpr ::std::span<value_type> span() noexcept { return { data(), size() }; }
	constexpr ::std::span<const value_type> span() const noexcept { return { data(), size() }; }

	constexpr auto begin() { return data(); }
	constexpr auto begin() const { return data(); }
	constexpr auto end() { return data() + size(); }
	constexpr auto end() const { return data() + size(); }
public:
	size_t _count = 0;
	::std::unique_ptr<value_type[]> _value = nullptr;
};

NGS_LIB_MODULE_END