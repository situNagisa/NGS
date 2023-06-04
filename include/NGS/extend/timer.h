#pragma once

#include "NGS/base/base.h"

NGS_BEGIN

template<class defaultDuration = std::chrono::microseconds>
class Duration {
public:
	NGS_TYPE_DEFINE(std::chrono::high_resolution_clock, clock);
	NGS_TYPE_DEFINE(defaultDuration, duration);
	NGS_TYPE_DEFINE(std::chrono::time_point<__clock>, point);

	void Update() {
		auto now = __clock::now();
		_dt = std::chrono::duration_cast<__duration>(now - _current);
	}
	void Record() { _current = __clock::now(); }
	uint64 DeltaCount()const { return _dt.count(); }
	__duration_ref Delta() { return _dt; }
	__duration_ref_cst Delta()const { return _dt; }

private:
	__point _current{};
	__duration _dt;
};

NGS_END