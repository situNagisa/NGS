#pragma once

#include "../defined.h"
#include "./config.h"

NGS_OS_ESP_IO_BEGIN

struct NGS_DLL_API gpio : embedded::io::gpio::gpio
{
	NGS_MPL_ENVIRON(gpio);
public:
	gpio();
	virtual ~gpio() override;

	virtual bool open(embedded::io::pin_t gpio_num, embedded::io::gpio::modes::io io_mode, embedded::io::gpio::modes::pull pull_mode) override;
	virtual bool is_opened() const override;
	virtual void close() override;
	virtual void reset() override;
	virtual void set_interrupt(bool enable) override;
	virtual void set_interrupt(embedded::io::gpio::modes::interrupt type) override;
	virtual void set_io(embedded::io::gpio::modes::io mode) override;
	virtual void set_pull(embedded::io::gpio::modes::pull mode) override;
	virtual void set(bool value) override;
	virtual bool get() const override;
	virtual embedded::io::pin_t get_pin() const override { return _pin; }

	bool open(embedded::io::pin_t gpio_num, const gpio_config& config);
protected:
	embedded::io::pin_t _pin = embedded::io::invalid_pin;
	gpio_config _config{};
};

NGS_OS_ESP_IO_END