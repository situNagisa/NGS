#pragma once

#include "NGS/extend/color/defined.h"
#include "NGS/extend/color/concept.h"

NGS_BEGIN
NGS_CONCEPT

template<typename T>
concept CChannel = requires(T t) {
	{ T::Count } -> std::convertible_to<size_t>;
	{ T::Offset } -> std::convertible_to<size_t>;
	{ T::Filter } -> std::convertible_to<size_t>;
	{ T::FilterWithOffset } -> std::convertible_to<size_t>;
	std::is_integral_v<typename T::type>;
};

NGS_END
NGS_END

NGS_COLOR_SPACE_BEGIN

template<size_t _Count, size_t _Offset = 0>
struct NGS_API Channel {
	static constexpr size_t Count = _Count;
	static constexpr size_t Offset = _Offset;

	using type = BitSet<Count>::type;

	static constexpr type Filter = BitSet<Count>::Mask;
	static constexpr  size_t FilterWithOffset = Filter << Offset;

	static constexpr float64 Percent(type value) {
		return static_cast<float64>(value) / Filter;
	}

	template<CChannel _Channel>
	static constexpr _Channel::type ConvertTo(type value) {
		//这里很关键！一定要检测非0，不然常量表达式不通过
		if constexpr (Filter)
			//这里也很关键！顺序不能改！常量表达式中不允许浮点数转换为整数，所以必须先乘再除
			return (size_t)value * _Channel::Filter / Filter;
		else
			return 0;
	}
	template<size_t _Count2, size_t _Offset2>
	static constexpr Channel<_Count2, _Offset2>::type ConvertTo(type value) {
		return ConvertTo < Channel<_Count2, _Offset2>>(value);
	}
	template<CChannel _Channel>
	static constexpr type ConvertFrom(_Channel::type value) {
		//这里很关键！一定要检测非0，不然常量表达式不通过
		if constexpr (_Channel::Filter)
			//这里也很关键！顺序不能改！常量表达式中不允许浮点数转换为整数，所以必须先乘再除
			return value * Filter / _Channel::Filter;
		else
			return 0;
	}
	template<size_t _Count2, size_t _Offset2>
	static constexpr type ConvertFrom(Channel<_Count2, _Offset2>::type value) {
		return ConvertFrom< Channel<_Count2, _Offset2>>(value);
	}

	static constexpr auto FilterColor(CIntegral auto color) {
		return (color >> Offset) & Filter;
	}
private:
	Channel() = default;
};
using Channel0 = Channel<0>;
using Channel1 = Channel<1>;
using Channel2 = Channel<2>;
using Channel3 = Channel<3>;
using Channel4 = Channel<4>;
using Channel5 = Channel<5>;
using Channel6 = Channel<6>;
using Channel7 = Channel<7>;
using Channel8 = Channel<8>;

using StdChannel = Channel8;

static_assert(CChannel<StdChannel>);

NGS_COLOR_SPACE_END
