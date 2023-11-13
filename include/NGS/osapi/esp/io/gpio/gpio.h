#pragma once

#include "./data.h"

NGS_OS_ESP_IO_BEGIN

struct NGS_DLL_API gpio : embedded::io::gpio::gpio
{
	NGS_MPL_ENVIRON(gpio);
public:
	gpio();
	virtual ~gpio() override;

	virtual bool open(embedded::io::pin_t gpio_num, embedded::io::gpio::modes::io io_mode) override;
	virtual bool is_open() const override;
	virtual void close() override;
	virtual void reset() override;
	virtual void set_interrupt(bool enable) override;
	virtual void set_interrupt(embedded::io::gpio::modes::interrupt type) override;
	virtual void set_mode(embedded::io::gpio::modes::io mode) override;
	virtual void set(bool value) override;
	virtual bool get() const override;

protected:
	gpio_data _data{};
};

NGS_OS_ESP_IO_END