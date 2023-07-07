#pragma once

#include "NGS/base/base.h"

NGS_BEGIN

template<typename _Duration, typename _Clock>
class Timer {
public:
	using clock = _Clock;
	using time_point = typename clock::time_point;
	using duration = _Duration;

public:

	void Update() {
		auto now = GET_NOW();
		_duration = std::chrono::duration_cast<duration>(now - _current);
		_current = now;
	}
	static time_point GET_NOW() { return clock::now(); }

	duration GetDuration()const { return _duration; }
	template<typename _Duration2>
	_Duration2 GetDuration()const { return std::chrono::duration_cast<_Duration2>(_duration); }

	//time_point GetRecordedTime()const { return _current; }
private:
	time_point _current = {};
	duration _duration = {};
};

using StdTimer = Timer< std::chrono::nanoseconds, std::chrono::high_resolution_clock>;

class DelayCall : public Singleton<DelayCall> {
public:
	NGS_TYPE_DEFINE(std::function<void()>, timer);

	class DelayCallUnit {
	public:
		DelayCallUnit(__timer timer, StdTimer::duration delay)
			: _timer(timer)
			, _duration(delay)
			, _current(StdTimer::GET_NOW())
		{}
		bool Update() {
			auto now = StdTimer::GET_NOW();
			if ((now - _current) < _duration)return false;
			_timer();
			return true;
		}
	private:
		__timer _timer = {};
		StdTimer::duration _duration = {};
		StdTimer::time_point _current = {};
	};
private:
	friend class Singleton<DelayCall>;
	DelayCall() = default;
public:
	void Update() {
		for (auto it = _timers.begin(); it != _timers.end(); ) {
			if (!it->Update()) {
				it++;
				continue;
			}
			it = _timers.erase(it);
		}
	}
	void SetTimer(__timer_ref_cst timer, StdTimer::duration delay) {
		_timers.emplace_back(timer, delay);
	}
private:
	std::list<DelayCallUnit> _timers;
};


NGS_END