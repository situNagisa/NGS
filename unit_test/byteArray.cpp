#include "defined.h"

TEST(base, byteArray) {
	ngs::ByteArray byteArray;
	float floating = 1.3333f;
	size_t unsignedIntegral = 0xFFFF;
	byteArray.Write(floating);
	byteArray.Write(unsignedIntegral);

	EXPECT_EQ(byteArray.Read<float>(), floating);
	EXPECT_EQ(byteArray.Read<size_t>(), unsignedIntegral);

	byteArray.Clear();
	byteArray.Bind(std::array{0x93, 0xA9, 0xAA, 0x3F});
	EXPECT_EQ(byteArray.Read<float>(), floating);
}
