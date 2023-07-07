#pragma once

#include "NGS/base/base.h"
#include "NGS/math/math.h"

#undef max

NGS_BEGIN

NGS_CONCEPT

/**
 * @brief 指定一个`解析函数`的约束，该函数实例具有形式`size_t(_Param)`
 *
 * @tparam _Function	指定检测的函数对象类型，该函数的实例具有形式`size_t(_Param)`
 * @tparam _Param		指定传递给该函数的参数类型
*/
template<typename _Function, typename _Param>
concept protocols_parser_step = requires(_Function function, _Param param) {
	{function(param)} -> std::convertible_to<size_t>;
};

/**
 * @brief 指定一个`可解析结构体`的约束
 *
 * @param Header	满足`sized_range`约束，其元素类型满足`convertible_to<byte>`约束，表示结构体需要以什么数据开头
 * @param Size		可转换为`size_t`类型，表示结构体所能接收的数据长度
 * @param Parse		满足`protocols_parser_step`约束，为一个函数，具有形式`size_t Parse(_Param)`或`size_t Parse<_Param>()`
 *
 * @tparam _Struct	检测的结构体
 * @tparam _Param	传递给Parse参数的类型，满足`protocols_parser_step`约束
 *
 * @see `ngs::protocols_parser_step`
 */
template<typename _Struct, typename _Param>
concept protocols_parsable = requires() {
	{_Struct::Header} -> std::ranges::sized_range<>;
	{_Struct::Size} -> std::convertible_to<size_t>;
		requires std::convertible_to<std::ranges::range_value_t<decltype(_Struct::Header)>, ngs::byte>;
		requires std::ranges::sized_range< _Param>;
} && (
	requires() {
		{_Struct::Parse} -> protocols_parser_step<_Param>;
} || requires() {
	{_Struct::template Parse<_Param>} -> protocols_parser_step<_Param>;
}
);

NGS_END

namespace protocols_parsers {
	static constexpr size_t size_lack = std::numeric_limits<size_t>::max();

	size_t parse_array(const std::ranges::sized_range auto& array, const std::ranges::sized_range auto& data) {
		if (std::ranges::size(data) < std::ranges::size(array))return 0;
		auto [result1, result2] = std::ranges::mismatch(array, data);
		if (result1 == array.end()) {
			return array.size();
		}
		return 0;
	}
	template<ngs::byte... _Array>
	size_t parse_array(const std::ranges::sized_range auto& data) {
		constexpr std::array<ngs::byte, sizeof...(_Array)> array = { _Array... };
		return parse_array(array, data);
	}
	template<ngs::byte _Low, ngs::byte _High>
	size_t parse_range(const std::ranges::input_range auto& data) {
		return ngs::In(*std::ranges::begin(data), _Low, _High);
	}
	template<ngs::byte... _Datas>
	size_t parse_equal_of(const std::ranges::input_range auto& data) {
		return ((*std::ranges::begin(data) == _Datas) || ...);
	}
	/**
	 * @brief 按照`可解析结构体`解析数据流`_Param data`
	 *
	 * @tparam _Struct 满足`protocols_parsable`约束
	 * @tparam _Param
	 *
	 * @param data 传递给`解析函数`的参数，满足`sized_range`约束
	 *
	 * @see `protocols_parsable`
	 *
	 * @return 解析的数据长度
	 */
	template<typename _Struct, typename _Param>
		requires protocols_parsable<_Struct, _Param>
	size_t parse_struct(const _Param& data) {
		size_t length = 0;
		int result = 0;
		if (std::ranges::size(data) < _Struct::Size)return size_lack;

		result = ngs::protocols_parsers::parse_array(_Struct::Header, data | std::views::drop(0));
		if (!result)return 0;
		length += result;

		result = _Struct::Parse(data | std::views::take(_Struct::Size));
		if (!result) return 0;
		length += result;

		return length;
	}

}
#undef _N
#undef _S

template<size_t _N>
class ProtocolsParser {
public:
	NGS_TYPE_DEFINE(ProtocolsParser<_N>, this);
	using ParsedSequence = std::conditional_t<_N != 0, std::array<ngs::byte, _N>, std::vector<ngs::byte>>;
	using ParseCB = size_t(const std::deque<ngs::byte>&);

public:
	ProtocolsParser() = default;
	ProtocolsParser(const std::function<ParseCB>& parser)
		: _parser(parser)
	{}

	void SetParser(const std::function<ParseCB>& parser) { _parser = parser; }
	void Update() {
		while (_data.size() && _Parse());
	}
	void Update(size_t parseTimes) {
		while (parseTimes-- && _data.size() && _Parse());
	}
	template<typename... Args>
	void In(ngs::byte data, Args... args) {
		In(data);
		In(args...);
	}
	template<typename T>
	__this_ref operator<<(T&& data) {
		In(std::forward<T>(data));
		return *this;
	}
	template<std::ranges::forward_range _Rng>
		requires std::same_as<ngs::byte, std::ranges::range_value_t<_Rng>>
	void In(const _Rng& range) {
		for (auto i : range) {
			In(i);
		}
	}
	template<typename T, size_t _S>
	void In(T(&data)[_S]) {
		for (size_t i = 0; i < _S * sizeof(T); i++)
			In(((ngs::byte_ptr)data)[i]);
	}
	void In(ngs::byte data) {
		//Debugger::PrintFormat("0x%02x ", data);
		_data.push_back(data);
	}
	size_t Size()const { return _data.size(); }
	void Clear() { _data.clear(); }

	size_t ParsedSize()const { return _parsed.size(); }
	ParsedSequence ParsedPop() {
		//ngs::nos.Log("ProtocolsParser::ParsedPop", "size:%d pop\n", _parsed.size());
		auto front = _parsed.front();
		_parsed.pop();
		return front;
	}
private:
	bool _Parse() {
		size_t length = _parser(_data);
		if (length == protocols_parsers::size_lack)return false;
		if (!length) {
			/*Debugger::Print(TextColor::RED);
			Debugger::PrintFormat("0x%02x ", _data.front());
			Debugger::Print(TextColor::RESERT);*/
			_data.pop_front();
			return true;
		}
		ParsedSequence& parsed = _parsed.emplace();
		//Debugger::Print(TextColor::GREEN);
		for (size_t i = 0; i < length; i++) {
			parsed[i] = (_data.front());
			//Debugger::PrintFormat("0x%02x ", _data.front());
			_data.pop_front();
		}
		//Debugger::PrintLine(TextColor::RESERT);
		//ngs::nos.Log("ProtocolsParser::_Parse", "length:%d rest data size:%d\n", length, _data.size());
		return true;
	}
private:
	std::function<ParseCB> _parser = nullptr;
	std::deque<ngs::byte> _data = {};
	std::queue<ParsedSequence> _parsed = {};
};

/**
 * @brief 按照结构体格式解析数据
 *
 * @tparam _Struct 满足`ngs::protocols_parsable`约束
 *
 * @see `ngs::protocols_parsable`
 */
template<typename _Struct>
class ProtocolsStructParser : public ProtocolsParser<_Struct::Size> {
private:
	NGS_TYPE_DEFINE(ProtocolsParser<_Struct::Size>, base);
public:
	ProtocolsStructParser()
		: __base(ngs::protocols_parsers::parse_struct<_Struct, std::deque<ngs::byte>>)
	{}
};

NGS_END
