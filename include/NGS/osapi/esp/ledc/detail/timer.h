#pragma once

#include "./allocator.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct ledc_timer
{
	NGS_PP_INJECT_BEGIN(ledc_timer);
public:
	ledc_timer(
		mode_resource& mode, 
		timer_resource&& timer,
		::ledc_timer_bit_t resolution,
		::std::uint32_t frequency,
		::ledc_clk_cfg_t clock
	)
		: _mode(mode)
		, _timer(::std::move(timer))
	{
		_configure(resolution, frequency, clock);
	}
	ledc_timer(self_type&&) = default;

	~ledc_timer()
	{
		_deconfigure();
	}

	void _configure(::ledc_timer_bit_t resolution, ::std::uint32_t frequency, ::ledc_clk_cfg_t clock) const
	{
		::ledc_timer_config_t config{
			.speed_mode = _mode.value(),
			.duty_resolution = resolution,
			.timer_num = _timer.value(),
			.freq_hz = frequency,
			.clk_cfg = clock,
			.deconfigure = false
		};
		auto result = ::ledc_timer_config(&config);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to configure ledc timer");
	}

	void _deconfigure() const
	{
		::ledc_timer_config_t config{
			.speed_mode = _mode.value(),
			.timer_num = _timer.value(),
			.deconfigure = true
		};
		auto result = ::ledc_timer_config(&config);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to deconfigure ledc timer");
	}

	void set_frequency(::std::uint32_t frequency) const
	{
		auto result = ::ledc_set_freq(_mode.value(), _timer.value(), frequency);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set ledc frequency");
	}

	[[nodiscard]] decltype(auto) get_frequency() const
	{
		return ::ledc_get_freq(_mode.value(), _timer.value());
	}

	void set(::std::uint32_t clock_divider, ::ledc_timer_bit_t resolution, ::ledc_clk_src_t clock) const
	{
		auto result = ::ledc_timer_set(_mode.value(), _timer.value(), clock_divider, resolution, clock);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set ledc timer");
	}

	void reset() const
	{
		auto result = ::ledc_timer_rst(_mode.value(), _timer.value());
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to reset ledc timer");
	}

	void pause() const
	{
		auto result = ::ledc_timer_pause(_mode.value(), _timer.value());
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to pause ledc timer");
	}

	void resume() const
	{
		auto result = ::ledc_timer_resume(_mode.value(), _timer.value());
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to resume ledc timer");
	}

	[[nodiscard]] auto&& mode() const { return _mode; }
	[[nodiscard]] auto&& timer() const { return _timer; }

	mode_resource& _mode;
	timer_resource _timer;
};

constexpr decltype(auto) duty_of(::ledc_timer_bit_t resolution, ::std::floating_point auto percent)
{
	return bits::algorithm::mask(::std::to_underlying(resolution)) * percent;
}

struct state_timer : ledc_timer
{
	NGS_PP_INJECT(state_timer);
public:
	state_timer(
		mode_resource& mode,
		timer_resource&& timer,
		::ledc_timer_bit_t resolution,
		::std::uint32_t frequency,
		::ledc_clk_cfg_t clock
	)
		: base_type(mode, ::std::move(timer), resolution, frequency, clock)
	{
		_resolution = resolution;
	}
	using base_type::operator=;

	void set(::std::uint32_t clock_divider, ::ledc_timer_bit_t resolution, ::ledc_clk_src_t clock)
	{
		_resolution = resolution;
		ledc_timer::set(clock_divider, resolution, clock);
	}

	[[nodiscard]] decltype(auto) get_resolution() const { return _resolution; }

	::ledc_timer_bit_t _resolution;
};

NGS_LIB_MODULE_END