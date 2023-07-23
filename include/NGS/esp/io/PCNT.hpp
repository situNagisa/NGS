#pragma once

#include "NGS/esp/io/PCNT.h"

NESP_BEGIN

struct _PCNTData {
	pcnt_unit_handle_t handle;
	pcnt_channel_handle_t
		a, b;
};


bool PCNT::Open(ngs::pin_t a, ngs::pin_t b, int high, int low)
{
	NGS_NEW(_data,_PCNTData);
	auto& data = *reinterpret_cast<_PCNTData*>(_data);

	//new unit
	{
		pcnt_unit_config_t unit_config = {};
		unit_config.low_limit = low;
		unit_config.high_limit = high;
		if (pcnt_new_unit(&unit_config, &data.handle) != ESP_OK) {
			NGS_LOGL(error,"pcnt new unit fail!");
			goto err_unit;
		}
	}
	{
		pcnt_glitch_filter_config_t filter_config = {};
		filter_config.max_glitch_ns = 1000;
		if (pcnt_unit_set_glitch_filter(data.handle, &filter_config) != ESP_OK) {
			NGS_LOGL(error, "pcnt set filter fail!");
			goto err_unit;
		}
	}
	//new channel
	{
		pcnt_chan_config_t channel_config = {};
		channel_config.edge_gpio_num = a;
		channel_config.level_gpio_num = b;
		if (pcnt_new_channel(data.handle, &channel_config, &data.a) != ESP_OK) {
			NGS_LOGL(error, "pcnt new channel a fail!");
			goto err_channel_a;
		}
		if (pcnt_channel_set_edge_action(data.a, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE) != ESP_OK) {
			NGS_LOGL(error, "pcnt set edge a fail!");
			goto err_channel_a;
		}
		if (pcnt_channel_set_level_action(data.a, PCNT_CHANNEL_LEVEL_ACTION_INVERSE, PCNT_CHANNEL_LEVEL_ACTION_KEEP) != ESP_OK) {
			NGS_LOGL(error, "pcnt set level a fail!");
			goto err_channel_a;
		}

		channel_config = {};
		channel_config.edge_gpio_num = b;
		channel_config.level_gpio_num = a;
		if (pcnt_new_channel(data.handle, &channel_config, &data.b) != ESP_OK) {
			NGS_LOGL(error, "pcnt new channel b fail!");
			goto err_channel_b;
		}
		if (pcnt_channel_set_edge_action(data.b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE) != ESP_OK) {
			NGS_LOGL(error, "pcnt set edge b fail!");
			goto err_channel_b;
		}
		if (pcnt_channel_set_level_action(data.b, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE) != ESP_OK) {
			NGS_LOGL(error, "pcnt set level b fail!");
			goto err_channel_b;
		}
	}
	NGS_LOGFL(debug,"open %d %d successfully!", a, b);
	Enable();
	Start();
	return true;
err_channel_b:;
	pcnt_del_channel(data.b);
err_channel_a:
	pcnt_del_channel(data.a);
err_unit:;
	pcnt_del_unit(data.handle);

	NGS_DELETE(&data);
	_data = nullptr;
	return false;
}

bool PCNT::IsOpened() const { return _data; }

void PCNT::Close() {
	auto& data = *reinterpret_cast<_PCNTData*>(_data);

	pcnt_del_channel(data.b);
	pcnt_del_channel(data.a);
	pcnt_unit_disable(data.handle);
	pcnt_del_unit(data.handle);

	NGS_DELETE(&data);
	_data = nullptr;
}

void PCNT::SetGlitchFilter(ngs::uint32 max_glitch_ns) {

}

int PCNT::GetPulseCount() const {
	auto& data = *reinterpret_cast<_PCNTData*>(_data);

	int count = 0;
	if (pcnt_unit_get_count(data.handle, &count) != ESP_OK) {
		NGS_LOGL(error, "get pulse count fail!");
		return 0;
	}

	return count;
}

void PCNT::ClearPulseCount() {
	auto& data = *reinterpret_cast<_PCNTData*>(_data);

	pcnt_unit_clear_count(data.handle);
}

void PCNT::Enable() {
	auto& data = *reinterpret_cast<_PCNTData*>(_data);

	pcnt_unit_enable(data.handle);
}

void PCNT::Disable() {
	auto& data = *reinterpret_cast<_PCNTData*>(_data);

	pcnt_unit_disable(data.handle);
}

void PCNT::Start() {
	auto& data = *reinterpret_cast<_PCNTData*>(_data);

	pcnt_unit_start(data.handle);
}

void PCNT::Stop() {
	auto& data = *reinterpret_cast<_PCNTData*>(_data);

	pcnt_unit_stop(data.handle);
}

NESP_END