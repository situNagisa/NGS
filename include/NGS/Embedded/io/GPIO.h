#pragma once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"
#include "NGS/Embedded/Interface.h"

NGS_BEGIN

class GPIO : public EmbeddedObject {
public:
	enum class Mode {
		disable,
		input,
		output,
		output_open_drain,
		input_output_open_drain,
		input_output,
	};
	enum class Pull {
		pullup,
		pulldown,
		pullup_pulldown,
		floating,
	};
	enum class Interrupt {
		disable,
		positive,
		nagative,
		any,
		low,
		high,
		max,
	};
public:

	bool Open(pin_t gpio_num) { Open(gpio_num, Mode::output); }
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
