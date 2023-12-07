#pragma once

#include "./concept.h"

NGS_LIB_MODULE_BEGIN

template<size_t _Count, size_t _Offset = 0>
struct NGS_DLL_API channel {
	static constexpr size_t count = _Count;
	static constexpr size_t offset = _Offset;

	using type = byte_<bits::as_byte(count)>;

	static constexpr type filter = static_cast<type>(bits::mask(count));
	static constexpr  size_t filter_with_offset = filter << offset;

	static constexpr float64 percent(type value) { return static_cast<float64>(value) / filter; }

	template<color_channel _Channel>
	static constexpr typename _Channel::type convert_to(type value) {
		//这里很关键！一定要检测非0，不然常量表达式不通过
		if constexpr (filter)
			//这里也很关键！顺序不能改！常量表达式中不允许浮点数转换为整数，所以必须先乘再除
			return static_cast<size_t>(value) * _Channel::filter / filter;
		else
			return 0;
	}
	template<size_t _Count2, size_t _Offset2>
	static constexpr typename channel<_Count2, _Offset2>::type convert_to(type value) {
		return convert_to< channel<_Count2, _Offset2>>(value);
	}
	template<color_channel _Channel>
	static constexpr type convert_from(typename _Channel::type value) {
		//这里很关键！一定要检测非0，不然常量表达式不通过
		if constexpr (_Channel::filter)
			//这里也很关键！顺序不能改！常量表达式中不允许浮点数转换为整数，所以必须先乘再除
			return value * filter / _Channel::filter;
		else
			return 0;
	}
	template<size_t _Count2, size_t _Offset2>
	static constexpr type convert_from(typename channel<_Count2, _Offset2>::type value) {
		return convert_from< channel<_Count2, _Offset2>>(value);
	}

	static constexpr auto filter_color(std::integral auto color) {
		return (color >> offset) & filter;
	}
private:
	channel() = default;
};
using channel0 = channel<0>;
using channel1 = channel<1>;
using channel2 = channel<2>;
using channel3 = channel<3>;
using channel4 = channel<4>;
using channel5 = channel<5>;
using channel6 = channel<6>;
using channel7 = channel<7>;
using channel8 = channel<8>;

using standard_channel = channel8;

static_assert(color_channel<standard_channel>);

NGS_LIB_MODULE_END

NGS_LIB_MODULE_EXPORT(channel);
NGS_LIB_MODULE_EXPORT(standard_channel);
