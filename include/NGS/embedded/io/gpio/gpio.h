#pragma once

#include "./mode.h"

NGS_EMBEDDED_IO_GPIO_BEGIN

struct NGS_DLL_API gpio : basic_io
{
	NGS_MPL_ENVIRON(gpio);
public:
	bool open(pin_t gpio_num) { return open(gpio_num, modes::io::output); }

	virtual bool open(pin_t gpio_num, modes::io io_mode) = 0;
	virtual void reset() = 0;

	virtual void set_interrupt(bool enable) = 0;
	virtual void set_interrupt(modes::interrupt type) = 0;

	virtual void set_mode(modes::io mode) = 0;

	virtual bool get() const = 0;
	virtual void set(bool value) = 0;


	void high() { set(true); }
	void low() { set(false); }

	virtual size_t read(void_ptr buffer, size_t size) override
	{
		std::memset(buffer, get(), size);
		return size;
	}

	virtual size_t write(void_ptr_cst buffer, size_t size) override
	{
		set(*static_cast<const bool*>(buffer + size - 1));
		return size;
	}
};

NGS_EMBEDDED_IO_GPIO_END