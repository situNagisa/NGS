#pragma once

#include "./mode.h"

NGS_EMBEDDED_IO_GPIO_BEGIN

struct NGS_DLL_API gpio : basic_io
{
	NGS_MPL_ENVIRON(gpio);
public:

	bool open(pin_t gpio_num)
	{
		return open(gpio_num, modes::io::disable, modes::pull::floating);
	}

	virtual bool open(pin_t gpio_num, modes::io io_mode, modes::pull pull_mode) = 0;
	virtual void reset() = 0;

	virtual void set_interrupt(bool enable) = 0;
	virtual void set_interrupt(modes::interrupt type) = 0;

	virtual void set_io(modes::io mode) = 0;
	virtual void set_pull(modes::pull mode) = 0;

	virtual bool get() const = 0;
	virtual void set(bool value) = 0;

	virtual pin_t get_pin() const = 0;

	void high() { set(true); }
	void low() { set(false); }

	virtual size_t read(void_ptr buffer, size_t size) override
	{
		std::memset(buffer, get(), size);
		return size;
	}

	virtual size_t write(void_ptr_cst buffer, size_t size) override
	{
		set(static_cast<const bool*>(buffer)[size - 1]);
		return size;
	}
};

NGS_EMBEDDED_IO_GPIO_END