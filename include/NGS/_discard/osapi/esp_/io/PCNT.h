#pragma once

#include "NGS/esp/defined.h"

NESP_BEGIN

class PCNT : public IO {
public:

public:

	bool Open(
		ngs::pin_t a, ngs::pin_t b,
		int high, int low
	);

	bool IsOpened()const;
	void Close();

	void SetGlitchFilter(ngs::uint32 max_glitch_ns);

	int GetPulseCount()const;
	void ClearPulseCount();

	void Enable();
	void Disable();
	void Start();
	void Stop();
private:

private:
	ngs::void_ptr _data = nullptr;
};

NESP_END
