#pragma once

#include "NGS/base/base.h"

NGS_BEGIN

class NGS_API  PWM : public IO{
public:

public:

	bool Open(pin_t pwm_num);
	bool IsOpened()const;
	void Set(float percent);
	void Close();
private:

private:
	void_ptr _data = nullptr;
};

NGS_END
