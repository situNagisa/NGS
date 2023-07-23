#include "defined.h"

TEST(communication, parse) {
	std::deque<ngs::byte> data{0xFF, 0xFF, 0x00, 0x80};
	int result;
	auto view = std::views::all(data);
	result = ngs::protocols_parsers::parse_array<0xFF, 0xFF, 0x00, 0x80>(view);
	EXPECT_EQ(result, 4);
	result = ngs::protocols_parsers::parse_array<0xFF, 0xFF, 0xFF, 0x80>(view);
	EXPECT_EQ(result, 0);
	result = ngs::protocols_parsers::parse_array<0xFF, 0xFF, 0x00, 0x80, 0x00>(view);
	EXPECT_EQ(result, 0);
}

TEST(communication, parser) {
	using ParsedSequence = std::array<ngs::byte, 11>;

	ngs::ProtocolsParser< 11>::ParseCB* parser = [](const std::deque<ngs::byte>& data)->size_t {
		size_t length = 0;
		size_t result = 0;
		if (data.size() < 11)return ngs::protocols_parsers::size_lack;

		result = ngs::protocols_parsers::parse_array<0xFF, 0xAA>(data | std::views::drop(0));
		if (!result)return 0;
		length += result;

		result = ngs::protocols_parsers::parse_range<0x50, 0x5A>(data | std::views::drop(length));
		if (!result) {
			result = ngs::protocols_parsers::parse_equal_of<0x5F>(data | std::views::drop(length));
			if (!result)return 0;
		}
		length += result;

		ngs::byte sum = 0;
		std::ranges::for_each_n(data.begin(), 10, [&sum](ngs::byte byte) { sum += byte; });
		if (sum != data[10])return 0;
		length += 8;

		return length;
	};
	std::vector< ParsedSequence> parsed;
	ngs::ProtocolsParser< 11> protocol(parser);
	ParsedSequence sequence = {};
	sequence[0] = 0xFF;
	sequence[1] = 0xAA;

	sequence[2] = 0x50;
	sequence[10] = sequence[0] + sequence[1] + sequence[2];
	protocol.In(sequence);
	protocol.Update();
	EXPECT_EQ(protocol.Size(), 0);
	parsed.push_back(protocol.ParsedPop());
	EXPECT_EQ(sequence, parsed.back());

	sequence[2] = 0x5F;
	sequence[10] = sequence[0] + sequence[1] + sequence[2];
	protocol.In(sequence);
	protocol.Update();
	EXPECT_EQ(protocol.Size(), 0);
	parsed.push_back(protocol.ParsedPop());
	EXPECT_EQ(sequence, parsed.back());

	sequence[2] = 0x00;
	sequence[10] = sequence[0] + sequence[1] + sequence[2];
	protocol.In(sequence);
	protocol.Update();
	EXPECT_EQ(protocol.Size(), sequence.size() - 1);
	EXPECT_EQ(protocol.ParsedSize(), 0);
}
struct DataSequence {
	static constexpr std::array<ngs::byte, 2> Header = { 0xFF,0xAA };
	static constexpr size_t Size = 11;
	static size_t Parse(std::ranges::sized_range auto data) {
		if (!ngs::protocols_parsers::parse_range<0x50, 0x5A>(data | std::views::drop(Header.size()))
			&& !ngs::protocols_parsers::parse_equal_of<0x5F>(data | std::views::drop(Header.size()))
			)
			return 0;

		ngs::byte sum = 0;
		std::ranges::for_each_n(std::ranges::begin(data), Size - 1, [&sum](ngs::byte byte) { sum += byte; });
		if (sum != *std::ranges::rbegin(data))return 0;

		return Size - Header.size();
	}
	using ParsedSequence = std::array<ngs::byte, Size>;
};

TEST(communication, parseStruct) {
	std::vector< DataSequence::ParsedSequence> parsed;
	ngs::ProtocolsStructParser<DataSequence> protocol;

	protocol.In(0xFF, 0xAA);
	ASSERT_EQ(protocol.Size(), 2);
	protocol.Update();
	ASSERT_EQ(protocol.Size(), 2);
	EXPECT_EQ(protocol.ParsedSize(), 0);

	DataSequence::ParsedSequence sequence = {};
	sequence[0] = 0xFF;
	sequence[1] = 0xAA;

	sequence[2] = 0x50;
	sequence[10] = sequence[0] + sequence[1] + sequence[2];
	protocol.In(sequence);
	ASSERT_EQ(protocol.Size(), 13);
	protocol.Update();
	ASSERT_EQ(protocol.Size(), 0);
	ASSERT_EQ(protocol.ParsedSize(), 1);
	parsed.push_back(protocol.ParsedPop());
	EXPECT_EQ(sequence, parsed.back());

	sequence[2] = 0x5F;
	sequence[10] = sequence[0] + sequence[1] + sequence[2];
	protocol.In(sequence);
	protocol.Update();
	EXPECT_EQ(protocol.Size(), 0);
	parsed.push_back(protocol.ParsedPop());
	EXPECT_EQ(sequence, parsed.back());

	sequence[2] = 0x00;
	sequence[10] = sequence[0] + sequence[1] + sequence[2];
	protocol.In(sequence);
	protocol.Update();
	EXPECT_EQ(protocol.Size(), sequence.size() - 1);
	EXPECT_EQ(protocol.ParsedSize(), 0);
}