#pragma  once

#include "NGS/base/base.h"
#include "NGS/extend/stream.h"

NGS_BEGIN

#if NGS_BUILD_TYPE == NGS_DEBUG

template<typename time = std::chrono::microseconds, typename clock = std::chrono::high_resolution_clock>
struct MeasureExecutionTime {
	using time_point = typename clock::time_point;

	MeasureExecutionTime(std::string message = "", const source_location& location = source_location::current())
		: _start(clock::now())
		, _location(location)
		, _message(message)
	{}
	~MeasureExecutionTime() {
		time_point end = clock::now();
		auto count = std::chrono::duration_cast<time>(end - _start);
		nos.Trace("\n=========================");
		nos.Trace(
			""
			"\n函数：%s"
			"\n运行时间：%d"
			, _location.function_name()
			, count.count()
		);

		if (!_message.empty()) {
			nos.Trace(
				""
				"\n附加信息：%s"
				, _message.c_str()
			);
		}
		nos.Trace("\n=========================\n");
	}
private:
	time_point _start;
	source_location _location;
	std::string _message;
};

#else

template<typename time = std::chrono::microseconds, typename clock = std::chrono::high_resolution_clock>
struct MeasureExecutionTime {
	MeasureExecutionTime(std::string message = "", source_location location = source_location::current()) {}
};

#endif

NGS_END