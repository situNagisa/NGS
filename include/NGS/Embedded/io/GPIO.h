#pragma once

#include "NGS/base/base.h"
#include "NGS/embedded/io/IO.h"

NGS_BEGIN

class NGS_DLL_API  GPIO : public IO {
public:
	enum class  Mode {
		disable,
		input,
		output,
		output_open_drain,
		input_output_open_drain,
		input_output,
	};
	enum class  Pull {
		pullup,
		pulldown,
		pullup_pulldown,
		floating,
	};
	enum class  Interrupt {
		disable,
		positive,
		nagative,
		any,
		low,
		high,
		max,
	};
public:

	bool Open(pin_t gpio_num) { return Open(gpio_num, Mode::output); }
	bool Open(pin_t gpio_num, Mode mode);

	bool IsOpened()const override;
	void Close() override;

	void Reset();

	void SetInterrupt(bool enable);
	void SetInterrupt(Interrupt type);

	void SetMode(Mode mode);

	bool Get() const;
	void Set(bool value);

	void High() { Set(true); }
	void Low() { Set(false); }
private:

private:

};

NGS_END
