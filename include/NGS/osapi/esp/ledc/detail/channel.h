#pragma once

#include "./allocator.h"
#include "./timer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct ledc_channel
{
	NGS_PP_INJECT_BEGIN(ledc_channel);
public:
	ledc_channel(
		mode_resource& mode, 
		channel_resource&& channel,
		const pin_resource& pin,
		const ledc_timer& timer,
		::ledc_intr_type_t interrupt = ::ledc_intr_type_t::LEDC_INTR_DISABLE,
		::std::uint32_t duty = {},
		int hpoint = {}
	)
		: _mode(mode)
		, _channel(::std::move(channel))
	{
		_configure(pin, timer, interrupt, duty, hpoint);
	}
	ledc_channel(self_type&&) = default;

	void _configure(const pin_resource& pin, const ledc_timer& timer, ::ledc_intr_type_t interrupt, ::std::uint32_t duty, int hpoint) const
	{
		::ledc_channel_config_t config{
				.gpio_num = pin.value(),
				.speed_mode = _mode.value(),
				.channel = _channel.value(),
				.intr_type = interrupt,
				.timer_sel = timer.timer().value(),
				.duty = duty,
				.hpoint = hpoint,
		};
		auto result = ::ledc_channel_config(&config);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to configure ledc channel");
	}

	void set_duty(::std::uint32_t duty) const
	{
		auto result = ::ledc_set_duty(_mode.value(), _channel.value(), duty);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set ledc duty");
	}

	void set_duty_with_hpoint(::std::uint32_t duty, ::std::uint32_t hpoint) const
	{
		auto result = ::ledc_set_duty_with_hpoint(_mode.value(), _channel.value(), duty, hpoint);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set duty width hpoint");
	}

	void update_duty() const
	{
		auto result = ::ledc_update_duty(_mode.value(), _channel.value());
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to update ledc duty");
	}

	decltype(auto) get_duty() const
	{
		return ::ledc_get_duty(_mode.value(), _channel.value());
	}

	void set_fade(::std::uint32_t target_duty,::ledc_duty_direction_t direction,::std::uint32_t step_num,::std::uint32_t duty_cycle_num,::std::uint32_t duty_scale) const
	{
		auto result = ::ledc_set_fade(_mode.value(), _channel.value(), target_duty, direction, step_num, duty_cycle_num, duty_scale);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set ledc fade");
	}

	void set_fade_with_step(::std::uint32_t target_duty,::std::uint32_t scale,::std::uint32_t cycle_num) const
	{
		auto result = ::ledc_set_fade_with_step(_mode.value(), _channel.value(), target_duty, scale, cycle_num);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set ledc fade with step");
	}

	void set_fade_with_time(::std::uint32_t target_duty,::std::uint32_t max_fade_time_ms) const{
		auto result = ::ledc_set_fade_with_time(_mode.value(), _channel.value(), target_duty, max_fade_time_ms);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set ledc fade with time");
	}

	void fade_start(::ledc_fade_mode_t mode) const
	{
		auto result = ::ledc_fade_start(_mode.value(), _channel.value(), mode);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to start ledc fade");
	}

#if SOC_LEDC_SUPPORT_FADE_STOP
	void fade_stop() const
	{
		auto result = ::ledc_fade_stop(_mode.value(), _channel.value());
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to stop ledc fade");
	}
#endif

	void set_duty_and_update(::std::uint32_t duty, ::std::uint32_t hpoint = {}) const
	{
		auto result = ::ledc_set_duty_and_update(_mode.value(), _channel.value(), duty, hpoint);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set duty width hpoint");
	}

	void set_fade_time_and_start(::std::uint32_t target_duty, ::std::uint32_t max_fade_time_ms, ::ledc_fade_mode_t mode) const
	{
		auto result = ::ledc_set_fade_time_and_start(_mode.value(), _channel.value(), target_duty, max_fade_time_ms, mode);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set ledc fade time and start");
	}

	void set_fade_step_and_start(::std::uint32_t target_duty,::std::uint32_t scale,::std::uint32_t cycle_num,::ledc_fade_mode_t mode) const
	{
		auto result = ::ledc_set_fade_step_and_start(_mode.value(), _channel.value(), target_duty, scale, cycle_num, mode);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set ledc fade with step and start");
	}

	[[nodiscard]] auto&& mode() const { return _mode; }
	[[nodiscard]] auto&& channel() const { return _channel; }

	mode_resource& _mode;
	channel_resource _channel;
};

NGS_LIB_MODULE_END