#pragma  once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"
#include "NGS/Debug/Stream.h"

NGS_BEGIN

#if NGS_HAS_CPP_20
using srouce_location = std::source_location;
#else
using srouce_location = std::experimental::source_location;
#endif

#if NGS_BUILD_TYPE == NGS_DEBUG

inline void Assert(
	bool b,
	nchar_ptr_cst text = "logic error",
	const srouce_location& location = srouce_location::current()
)
{
	if (b)return;
	nos.Error(
		""
		"\n========================="
		"\nERROR::[ %s ]"
		"\n文件：%s"
		"\n函数：%s"
		"\n第 %d 行，第 %d 列"
		"\n=========================\n",
		text,
		location.file_name(),
		location.function_name(),
		location.line(),
		location.column()
	);
	abort();
}

#else

inline void Assert(
	bool b,
	nchar_ptr_cst text = {},
	...
)

{
}

#endif // _DEBUG


template<typename time = std::chrono::microseconds, typename clock = std::chrono::high_resolution_clock>
struct MeasureExecutionTime {
	using time_point = clock::time_point;

	MeasureExecutionTime(std::string message = "", srouce_location location = srouce_location::current())
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
		//static_cast<ngs::ostream>(nos) << count;
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
	srouce_location _location;
	std::string _message;
};

NGS_END