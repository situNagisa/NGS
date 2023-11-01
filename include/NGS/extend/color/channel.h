#pragma once

#include "NGS/extend/color/defined.h"
#include "NGS/extend/color/concept.h"

NGS_BEGIN
NGS_CONCEPT

template<typename _Type>
concept CChannel = requires(_Type t) {
	{ _Type::count } -> std::convertible_to<size_t>;
	{ _Type::offset } -> std::convertible_to<size_t>;
	{ _Type::filter } -> std::convertible_to<size_t>;
	{ _Type::filter_with_offset } -> std::convertible_to<size_t>;
	std::is_integral_v<typename _Type::type>;

	//{ _Type::PERCENT(0) } -> std::convertible_to<float64>;
	//{ _Type::template CONVERT_TO<_Type> };
	//{ _Type::template CONVERT_FROM<_Type> };
	//{ _Type::FILTER_COLOR(0) };
};

NGS_END
NGS_END

NGS_COLOR_SPACE_BEGIN

template<size_t _Count, size_t _Offset = 0>
struct NGS_DLL_API Channel {
	static constexpr size_t count = _Count;
	static constexpr size_t offset = _Offset;

	using type = typename BitSet<count>::type;

	static constexpr type filter = BitSet<count>::Mask;
	static constexpr  size_t filter_with_offset = filter << offset;

	static constexpr float64 PERCENT(type value) {
		return static_cast<float64>(value) / filter;
	}

	template<CChannel _Channel>
	static constexpr typename _Channel::type CONVERT_TO(type value) {
		//这里很关键！一定要检测非0，不然常量表达式不通过
		if constexpr (filter)
			//这里也很关键！顺序不能改！常量表达式中不允许浮点数转换为整数，所以必须先乘再除
			return static_cast<size_t>(value) * _Channel::filter / filter;
		else
			return 0;
	}
	template<size_t _Count2, size_t _Offset2>
	static constexpr typename Channel<_Count2, _Offset2>::type CONVERT_TO(type value) {
		return CONVERT_TO < Channel<_Count2, _Offset2>>(value);
	}
	template<CChannel _Channel>
	static constexpr type CONVERT_FROM(typename _Channel::type value) {
		//这里很关键！一定要检测非0，不然常量表达式不通过
		if constexpr (_Channel::filter)
			//这里也很关键！顺序不能改！常量表达式中不允许浮点数转换为整数，所以必须先乘再除
			return value * filter / _Channel::filter;
		else
			return 0;
	}
	template<size_t _Count2, size_t _Offset2>
	static constexpr type CONVERT_FROM(typename Channel<_Count2, _Offset2>::type value) {
		return CONVERT_FROM< Channel<_Count2, _Offset2>>(value);
	}

	static constexpr auto FILTER_COLOR(CIntegral auto color) {
		return (color >> offset) & filter;
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
