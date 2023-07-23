#pragma once

#include "NGS/esp/defined.h"
#include "NGS/esp/esp_idf.h"


NESP_BEGIN
_NGS_PRIV_BEGIN

struct PWMData {
	ledc_timer_config_t timer;
	ledc_channel_config_t channel;
};

ngs::NumberAllocator<ledc_channel_t::LEDC_CHANNEL_MAX> s_channels;
ngs::NumberAllocator<ledc_timer_t::LEDC_TIMER_MAX> s_timers;

static constexpr auto S_SPEED_MODE = LEDC_LOW_SPEED_MODE;
static constexpr auto S_DUTY_RESOLUTION = LEDC_TIMER_13_BIT;
static constexpr auto S_FREQUENCY = 5000;

NGS_END
NESP_END

NGS_BEGIN

NGS_HPP_INLINE bool PWM::Open(ngs::pin_t pin) {
	using namespace esp::priv;

	ledc_timer_t timer = (ledc_timer_t)s_timers.Allocate();
	ledc_channel_t channel = (ledc_channel_t)s_channels.Allocate();
	esp_err_t ret = ESP_OK;

	if (timer < 0) return false;
	if (channel < 0) return false;

	NGS_NEW(_data, PWMData);
	auto& data = *(PWMData*)_data;

	ledc_timer_config_t& ledc_timer = data.timer;
	ledc_timer.speed_mode = S_SPEED_MODE;
	ledc_timer.timer_num = timer;
	ledc_timer.duty_resolution = S_DUTY_RESOLUTION;
	ledc_timer.freq_hz = S_FREQUENCY;
	ledc_timer.clk_cfg = LEDC_AUTO_CLK;

	ESP_ERROR_CHECK_WITHOUT_ABORT(ret = ledc_timer_config(&ledc_timer));
	if (ret != ESP_OK) {
		s_timers.Free((size_t)timer);
		s_channels.Free((size_t)channel);
		ngs::Delete(&data);
		_data = nullptr;
		return false;
	}

	ledc_channel_config_t& ledc_channel = data.channel;
	ledc_channel.speed_mode = S_SPEED_MODE;
	ledc_channel.channel = channel;
	ledc_channel.timer_sel = timer;
	ledc_channel.intr_type = LEDC_INTR_DISABLE;
	ledc_channel.gpio_num = pin;
	ledc_channel.duty = 0;
	ledc_channel.hpoint = 0;

	ESP_ERROR_CHECK_WITHOUT_ABORT(ret = ledc_channel_config(&ledc_channel));
	if (ret != ESP_OK) {
		s_timers.Free((size_t)timer);
		s_channels.Free((size_t)channel);
		ngs::Delete(&data);
		_data = nullptr;
		return false;
	}
	NGS_LOGFL(debug, " pin:%ld channel:%d timer:%d success!", pin, channel, timer);
	return true;
}

NGS_HPP_INLINE bool PWM::IsOpened()const { return _data; }

NGS_HPP_INLINE void PWM::Close() {
	using namespace esp::priv;

	auto& data = *(PWMData*)_data;
	ledc_timer_config_t& timer = data.timer;
	ledc_channel_config_t& channel = data.channel;

	s_timers.Free((size_t)timer.timer_num);
	s_channels.Free((size_t)channel.channel);

	NGS_DELETE(&data);
	_data = nullptr;
}

NGS_HPP_INLINE void PWM::Set(float percent) {
	using namespace esp::priv;

	auto& data = *(PWMData*)_data;
	ledc_channel_config_t& channel = data.channel;

	ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_set_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)channel.channel, percent * bit::mask((uint64)S_DUTY_RESOLUTION)));
	ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_update_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)channel.channel));
}

NGS_END