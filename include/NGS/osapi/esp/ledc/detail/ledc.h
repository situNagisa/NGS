#pragma once

#include "./allocator.h"
#include "./channel.h"
#include "./timer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

inline decltype(auto) find_suitable_duty_resolution(::std::uint32_t clock_source_frequency, ::std::uint32_t timer_frequency)
{
	return ::ledc_find_suitable_duty_resolution(clock_source_frequency, timer_frequency);
}

template<class Channel, class Timer>
struct basic_ledc
{
	NGS_PP_INJECT_BEGIN(basic_ledc);
public:
	using channel_type = Channel;
	using timer_type = Timer;

	basic_ledc(mode_resource&& mode, channel_type&& channel, timer_type&& timer, pin_resource&& pin)
		: _mode(::std::move(mode))
		, _channel(::std::move(channel))
		, _timer(::std::move(timer))
		, _pin(::std::move(pin))
	{
	}
	basic_ledc(self_type&&) = default;
	self_type& operator=(self_type&&) = default;

	[[nodiscard]] auto&& mode() const { return _mode; }
	[[nodiscard]] auto&& channel() const { return _channel; }
	[[nodiscard]] auto&& timer() const { return _timer; }
	[[nodiscard]] auto&& pin() const { return _pin; }

	mode_resource _mode;
	channel_type _channel;
	timer_type _timer;
	pin_resource _pin;
};


inline auto make_ledc(
	mode_resource&& mode,
	channel_resource&& channel,
	timer_resource&& timer,
	pin_resource&& pin,
	::ledc_timer_bit_t resolution,
	::std::uint32_t frequency,
	::ledc_clk_cfg_t clock,
	::ledc_intr_type_t interrupt = ::ledc_intr_type_t::LEDC_INTR_DISABLE,
	::std::uint32_t duty = {},
	int hpoint = {}
)
{
	auto t = ledc_timer(mode, ::std::move(timer), resolution, frequency, clock);
	auto c = ledc_channel(mode, ::std::move(channel), pin, t, interrupt, duty, hpoint);
	return basic_ledc(::std::move(mode), ::std::move(c), ::std::move(t), ::std::move(pin));
}

NGS_LIB_MODULE_END