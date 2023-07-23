#include "defined.h"

TEST(base, bit) {
	using Bit = ngs::BitSet<11>;
	Bit flag;
	flag = 0b010'11000011;

	EXPECT_FALSE(flag.All());
	EXPECT_TRUE(flag.Any());
	EXPECT_FALSE(flag.None());
	EXPECT_EQ(flag.Width(), 10);
	EXPECT_EQ(flag.Count(), 5);
	EXPECT_EQ(flag.LeadingOne(), 0);
	EXPECT_EQ(flag.LeadingZero(), 1);
	EXPECT_EQ(flag.TrailingZero(), 0);
	EXPECT_EQ(flag.TrailingOne(), 2);

	flag[0] = false;
	flag[1] = false;

	EXPECT_EQ(flag.TrailingOne(), 0);
	EXPECT_EQ(flag.TrailingZero(), 6);

	enum class _Flag_Sequence {
		is_555,
		is_666,
	};
	constexpr ngs::Flag
		is_555 = ngs::Flag((ngs::uint64)_Flag_Sequence::is_555),
		is_666 = ngs::Flag((ngs::uint64)_Flag_Sequence::is_666)
		;
	flag.Reset();
	flag.Set(is_555 | is_666);
	EXPECT_EQ(flag.Count(), 2);
}
